# ATM

## 需求陈述

  某银行拟开发一个自动取款机系统，它是一个由自动取款机、中央计算机、分行计算机及柜员终端组成的网络系统。ATM和中央计算机由总行投资购买。总行拥有多台 ATM，分别设在全市各主要街道上。分行负责提供分行计算机和柜员终端。柜员终端设在分行营业厅及分行下属的各个储蓄所内。该系统的软件开发成本由各个分行分摊。
       
  银行柜员使用柜员终端处理储户提交的储蓄事务。储户可以用现金或支票向自己拥有的某个账户内存款或开新账户。储户也可以从自己的账户中取款。通常，一个储户可能拥有多个账户。柜员负责把储户提交的存款或取款事务输进柜员终端，接收储户交来的现金或支票，或付给储户现金。柜员终端与相应的分行计算机通信，分行计算机具体处理针对某个账户的事务并且维护账户。

  拥有银行账户的储户有权申请领取现金兑换卡。使用现金兑换卡可以通过ATM访问自己的账户。目前仅限于用现金兑换卡在ATM上提取现金（即取款），或查询有关自己账户的信息（例如，某个指定账户上的余额）。将来可能还要求使用ATM办理转账、存款等事务。
    
  所谓现金兑换卡就是一张特制的磁卡，上面有分行代码和卡号。分行代码唯一标识总行下属的一个分行，卡号确定了这张卡可以访问哪些账户。通常，一张卡可以访问储户的若干个账户，但是不一定能访问这个储户的全部账户。每张现金兑换卡仅属于一个储户所有，但是，同一张卡可能有多个副本，因此，必须考虑同时在若干台ATM上使用同样的现金兑换卡的可能性。也就是说，系统应该能够处理并发的访问。

  当用户把现金兑换卡插入 ATM 之后，ATM 就与用户交互，以获取有关这次事务的信息，并与中央计算机交换关于事务的信息。首先，ATM 要求用户输入密码，接下来 ATM 把从这张卡上读到的信息以及用户输入的密码传给中央计算机，请求中央计算机核对这些信息并处理这次事务。中央计算机根据卡上的分行代码确定这次事务与分行的对应关系，并且委托相应的分行计算机验证用户密码。如果用户输入的密码是正确的，ATM 就要求用户选择事务类型（取款、查询等）。当用户选择取款时，ATM 请求用户输入取款额。最后，ATM 从现金出口吐出现金，并且打印出账单交给用户。

## 类与对象候选者

总行，分行，自动取款机（ATM），中央计算机，分行计算机，柜员终端，柜员，储户，账户，现金兑换卡（磁卡），卡片副本，事务（交易），账单（凭条）。

## 系统定义

目标：建设一个由 ATM、中央计算机、分行计算机、柜员终端构成的银行系统网络。

支持：
ATM：持卡认证、余额查询、现金取款（近期范围）
柜面：开户、存款（现金/支票）、柜台取款
中央机：分行路由与事务编排
分行机：账户与交易处理

近期不做但需预留：ATM 转账、ATM 存款。

边界：系统边界包含四类节点（ATM/中央机/分行机/柜员终端）及其间通信；外部实体为“客户/储户、柜员、运维”等。

基础假设
硬件：ATM 具备读卡器、加密键盘、出钞机、打印机；中央/分行机稳定在线。
合规模块（占位）：KYC、反洗钱、风控策略可后续接入，不影响当前接口。
面额：取款金额需为 ATM 实际支持的面额组合倍数（如 100 元倍数）

## 参与者

持卡客户（Customer）：在 ATM 上完成认证、选择并执行业务（取款/查询）。
储户（Depositor）：在柜面开新账户、办理现金/支票存款、柜台取款（可能与“持卡客户”同一人，但在柜面无卡也可办理）。
柜员（Teller）：在柜员终端录入柜面业务，收付现金/支票。
中央计算机（CentralHost）：按卡片分行代码定位交易所属分行并转发请求。
分行计算机（BranchHost）：校验 PIN（个人识别码）、维护账户、处理记账、控制并发。
ATM 设备（ATMDevice）：读卡器、PIN 键盘（用于输入个人识别码的设备）、出钞模块、打印机。
运维（Ops）：补钞、巡检、监控与告警（可选参与者）。


## 对象模型

### 实体对象（Entity）

#### Account（账户）

- **职责**：代表客户的银行业务实体，存储账户基本信息和状态
- **属性**：
  - accountNumber: String（主键，16 位数字）
  - balance: Decimal（精度 2 位，非负）
  - status: Enum{ACTIVE, FROZEN, CLOSED}
  - accountType: Enum{SAVINGS, CHECKING, CREDIT}
  - dailyWithdrawLimit: Decimal（默认 20000.00）
  - dailyWithdrawn: Decimal（每日重置为 0）
  - version: Integer（乐观锁版本号）
  - createdAt: DateTime
  - updatedAt: DateTime
- **方法**：
  - withdraw(amount: Decimal): Result<Transaction, ErrorCode>
    - 前置条件：status==ACTIVE && balance>=amount && dailyWithdrawn+amount<=dailyWithdrawLimit
    - 后置条件：balance 减少 amount，dailyWithdrawn 增加 amount，version 递增
  - deposit(amount: Decimal): Result<Transaction, ErrorCode>
  - checkBalance(): Decimal
  - freeze(): void
  - unfreeze(): void
- **关系**：
  - 属于(1..1) → Customer
  - 绑定(1..\*) → Card
  - 包含(1..\*) → Transaction

#### Customer（客户）

- **职责**：代表银行客户，管理个人信息和账户关系
- **属性**：
  - customerId: String（主键，UUID）
  - name: String（客户姓名）
  - idNumber: String（身份证号，唯一）
  - phone: String（联系电话）
  - address: String（联系地址）
  - status: Enum{ACTIVE, INACTIVE, BLACKLISTED}
  - createdAt: DateTime
- **方法**：
  - createAccount(accountType: AccountType): Result<Account, ErrorCode>
  - getAccounts(): List<Account>
  - updateProfile(profile: CustomerProfile): void
  - freezeAccount(accountNumber: String): void
- **关系**：
  - 拥有(1..\*) → Account
  - 关联(1..\*) → Card

#### Card（银行卡）

- **职责**：代表银行卡，存储卡片信息和状态
- **属性**：
  - cardNumber: String（主键，16 位数字）
  - cardType: Enum{DEBIT, CREDIT}
  - holderName: String（持卡人姓名）
  - expiryDate: Date（有效期）
  - status: Enum{VALID, EXPIRED, LOST, STOLEN, BLOCKED}
  - pinHash: String（PIN 码哈希值）
  - issueDate: DateTime
  - lastUsedDate: DateTime
- **方法**：
  - validateCard(): Boolean
  - verifyPIN(pin: String): Boolean
  - blockCard(): void
  - unblockCard(): void
- **关系**：
  - 绑定(1..1) → Account
  - 属于(1..1) → Customer

#### Transaction（交易）

- **职责**：记录所有银行交易信息
- **属性**：
  - transactionId: String（主键，UUID）
  - transactionType: Enum{WITHDRAWAL, DEPOSIT, TRANSFER, QUERY}
  - amount: Decimal（交易金额）
  - currency: String（货币类型，默认 CNY）
  - status: Enum{PENDING, SUCCESS, FAILED, CANCELLED}
  - fromAccount: String（转出账户）
  - toAccount: String（转入账户，可选）
  - atmId: String（ATM 设备 ID）
  - timestamp: DateTime
  - description: String（交易描述）
- **方法**：
  - process(): Result<Transaction, ErrorCode>
  - cancel(): void
  - getReceipt(): Receipt
- **关系**：
  - 属于(1..1) → Account
  - 关联(1..1) → ATM

### 边界对象（Boundary）

#### ATMInterface（ATM 接口）

- **职责**：处理 ATM 硬件交互和用户界面
- **属性**：
  - atmId: String（ATM 设备唯一标识）
  - location: String（ATM 位置）
  - status: Enum{ONLINE, OFFLINE, MAINTENANCE, ERROR}
  - cashAvailable: Integer（可用现金数量）
  - cashDenominations: Map<Integer, Integer>（面额分布）
  - lastMaintenanceDate: DateTime
- **方法**：
  - readCard(): Result<CardInfo, ErrorCode>
  - dispenseCash(amount: Integer): Result<Boolean, ErrorCode>
  - printReceipt(transaction: Transaction): Result<Receipt, ErrorCode>
  - displayMessage(message: String): void
  - ejectCard(): void
  - retractCard(): void
- **关系**：
  - 使用(1..1) → CardReader
  - 使用(1..1) → CashDispenser
  - 使用(1..1) → Printer
  - 使用(1..1) → Keypad

#### TellerInterface（柜员接口）

- **职责**：处理柜员终端交互
- **属性**：
  - terminalId: String（终端 ID）
  - tellerId: String（柜员 ID）
  - status: Enum{ACTIVE, INACTIVE, LOCKED}
  - lastLoginTime: DateTime
- **方法**：
  - login(tellerId: String, password: String): Result<Boolean, ErrorCode>
  - logout(): void
  - processAccountOpening(customerInfo: CustomerInfo): Result<Account, ErrorCode>
  - processDeposit(accountNumber: String, amount: Decimal): Result<Transaction, ErrorCode>
  - processWithdrawal(accountNumber: String, amount: Decimal): Result<Transaction, ErrorCode>
- **关系**：
  - 使用(1..1) → TellerTerminal
  - 关联(1..1) → Teller

#### CentralHostInterface（中央主机接口）

- **职责**：处理中央计算机的网络通信
- **属性**：
  - hostId: String（主机 ID）
  - status: Enum{ONLINE, OFFLINE, MAINTENANCE}
  - connectedBranches: List<String>（连接的分行列表）
  - messageQueue: Queue<Message>（消息队列）
- **方法**：
  - routeMessage(message: Message): Result<Message, ErrorCode>
  - broadcastMessage(message: Message): void
  - getBranchStatus(branchCode: String): BranchStatus
- **关系**：
  - 连接(1..\*) → BranchHost
  - 管理(1..\*) → ATM

### 控制对象（Control）

#### AuthenticationController（认证控制器）

- **职责**：协调身份认证流程
- **方法**：
  - authenticateCard(cardInfo: CardInfo): Result<Session, ErrorCode>
  - verifyPIN(sessionId: String, pin: String): Result<Boolean, ErrorCode>
  - createSession(customerId: String): Session
  - invalidateSession(sessionId: String): void
- **关系**：
  - 依赖 → CardService
  - 依赖 → CustomerService
  - 使用 → SessionManager

#### WithdrawalController（取款控制器）

- **职责**：协调取款业务流程
- **方法**：
  - processWithdrawal(sessionId: String, amount: Decimal): Result<Transaction, ErrorCode>
  - validateWithdrawalAmount(amount: Decimal): Boolean
  - checkDailyLimit(accountNumber: String, amount: Decimal): Boolean
  - lockAccount(accountNumber: String): Boolean
  - unlockAccount(accountNumber: String): void
- **关系**：
  - 依赖 → AccountService
  - 依赖 → TransactionService
  - 使用 → ATMInterface
  - 使用 → CentralHostInterface

#### TransactionController（交易控制器）

- **职责**：协调所有交易处理
- **方法**：
  - processTransaction(transaction: Transaction): Result<Transaction, ErrorCode>
  - rollbackTransaction(transactionId: String): Result<Boolean, ErrorCode>
  - retryTransaction(transactionId: String): Result<Transaction, ErrorCode>
  - getTransactionHistory(accountNumber: String): List<Transaction>
- **关系**：
  - 依赖 → AccountService
  - 依赖 → TransactionService
  - 使用 → CentralHostInterface

#### MessageController（消息控制器）

- **职责**：处理系统间消息传递
- **方法**：
  - sendMessage(message: Message): Result<Message, ErrorCode>
  - receiveMessage(): Message
  - processMessage(message: Message): Result<Response, ErrorCode>
  - handleTimeout(messageId: String): void
- **关系**：
  - 使用 → MessageQueue
  - 依赖 → NetworkService

### 对象关系图

```
Customer ||--o{ Account : "拥有"
Account ||--o{ Card : "绑定"
Account ||--o{ Transaction : "包含"
Customer ||--o{ Card : "关联"

ATMInterface ..> CardReader : "使用"
ATMInterface ..> CashDispenser : "使用"
ATMInterface ..> Printer : "使用"
ATMInterface ..> Keypad : "使用"

AuthenticationController ..> CardService : "依赖"
AuthenticationController ..> CustomerService : "依赖"
WithdrawalController ..> AccountService : "依赖"
WithdrawalController ..> TransactionService : "依赖"

CentralHostInterface ||--o{ BranchHost : "连接"
CentralHostInterface ||--o{ ATM : "管理"

MessageController ..> MessageQueue : "使用"
MessageController ..> NetworkService : "依赖"
```

### 设计模式应用

#### 策略模式

- **AccountTypeStrategy**：处理不同账户类型的行为差异
- **TransactionTypeStrategy**：处理不同交易类型的处理逻辑

#### 观察者模式

- **TransactionObserver**：监听交易状态变化，触发相应处理
- **ATMStatusObserver**：监听 ATM 状态变化，通知运维系统

#### 工厂模式

- **TransactionFactory**：根据交易类型创建相应的交易对象
- **MessageFactory**：根据消息类型创建相应的消息对象

#### 单例模式

- **SessionManager**：管理所有用户会话
- **ConfigurationManager**：管理系统配置信息

## 术语表

| 术语         | 英文                           | 定义                                   | 备注                |
| ------------ | ------------------------------ | -------------------------------------- | ------------------- |
| 持卡客户     | Customer                       | 在 ATM 端使用银行卡进行自助服务的用户  | 与储户可能是同一人  |
| 储户         | Account Holder                 | 在银行开设账户的客户，可在柜面办理业务 | 柜面业务主体        |
| 柜员         | Teller                         | 在柜员终端为储户办理业务的银行工作人员 | 柜面操作员          |
| 系统管理员   | System Administrator           | 负责系统运维、监控和故障处理的技术人员 | 运维人员            |
| PIN          | Personal Identification Number | 个人识别码，4-6 位数字密码             | 银行卡密码          |
| 分行代码     | Branch Code                    | 标识银行分行的唯一编码                 | 卡片磁条中存储      |
| 事务         | Transaction                    | 一次完整的银行业务操作                 | 具有 ACID 特性      |
| 凭条         | Receipt                        | ATM 打印的交易凭证                     | 包含交易明细        |
| 会话         | Session                        | 用户登录后的有效期间                   | 30 秒超时           |
| 乐观锁       | Optimistic Locking             | 通过版本号控制并发访问的机制           | 防止数据冲突        |
| 两阶段提交   | Two-Phase Commit               | 分布式事务的提交协议                   | 保证数据一致性      |
| 消息队列     | Message Queue                  | 异步消息传递的缓冲机制                 | 提高系统可靠性      |
| 负载均衡     | Load Balancing                 | 将请求分散到多个服务器的技术           | 提高系统性能        |
| 审计日志     | Audit Log                      | 记录系统操作历史的日志                 | 用于安全审计        |
| 硬件安全模块 | HSM                            | Hardware Security Module，硬件加密设备 | 保护 PIN 等敏感数据 |
| 数字证书     | Digital Certificate            | 用于身份验证的电子凭证                 | 确保通信安全        |
| 端到端加密   | End-to-End Encryption          | 从发送方到接收方的全程加密             | 保护数据传输安全    |
| 分布式事务   | Distributed Transaction        | 跨多个系统的事务处理                   | 保证数据一致性      |
| 故障恢复     | Fault Recovery                 | 系统故障后的自动恢复机制               | 提高系统可用性      |
| 并发控制     | Concurrency Control            | 控制多用户同时访问的机制               | 防止数据冲突        |

## 非功能需求

暂不分析
## 用例分析

### 参与者澄清

为了明确系统边界和用例范围，需要对参与者进行澄清：

- **持卡客户（Customer）**：在 ATM 端使用银行卡进行自助服务的用户
- **储户（Account Holder）**：在银行开设账户的客户，可在柜面办理业务（与持卡客户可能是同一人）
- **柜员（Teller）**：在柜员终端为储户办理业务的银行工作人员
- **系统管理员（Admin）**：负责系统运维、监控和故障处理的技术人员

### 用例列表

#### ATM 端用例

1. **UC-ATM-01**：持卡认证
2. **UC-ATM-02**：余额查询
3. **UC-ATM-03**：现金取款
4. **UC-ATM-04**：修改密码（预留）
5. **UC-ATM-05**：转账（预留）

#### 柜面端用例

1. **UC-TELLER-01**：开户
2. **UC-TELLER-02**：现金存款
3. **UC-TELLER-03**：支票存款
4. **UC-TELLER-04**：柜台取款
5. **UC-TELLER-05**：账户管理

#### 系统管理用例

1. **UC-ADMIN-01**：ATM 状态监控
2. **UC-ADMIN-02**：补钞管理
3. **UC-ADMIN-03**：故障处理

### 用例详细描述

#### UC-ATM-01：持卡认证

**参与者**：

- 主参与者：持卡客户
- 辅助参与者：ATM 设备、中央计算机、分行计算机

**前置条件**：

- ATM 设备正常运行
- 网络连接正常
- 银行卡未损坏

**主流程**：

1. 客户插入银行卡
2. ATM 读取卡片信息（卡号、分行代码、有效期）
3. 系统验证卡片有效性（未过期、未挂失）
4. 系统提示输入 PIN 码
5. 客户通过加密键盘输入 PIN 码
6. ATM 发送认证请求到中央计算机
7. 中央计算机根据分行代码路由到对应分行计算机
8. 分行计算机验证 PIN 码
9. 分行计算机返回认证结果
10. 中央计算机转发结果到 ATM
11. ATM 显示认证成功，进入主菜单

**异常流程**：

- **E1**：卡片无效（过期/挂失/损坏）
  - 系统显示"卡片无效，请联系银行"
  - 退卡，流程结束
- **E2**：PIN 码错误
  - 错误计数+1
  - 如果错误次数<3：提示重新输入 PIN
  - 如果错误次数=3：锁卡，显示"卡片已锁定，请联系银行"
  - 退卡，流程结束
- **E3**：网络超时
  - 重试 3 次
  - 如果仍超时：显示"网络异常，请稍后重试"
  - 退卡，流程结束
- **E4**：账户状态异常（冻结/关闭）
  - 显示"账户状态异常，请联系银行"
  - 退卡，流程结束

**后置条件**：

- 客户身份已验证
- 会话已建立（30 秒超时）
- 可进行后续业务操作

**用例关系**：

- 被包含于：所有 ATM 业务用例

#### UC-ATM-02：余额查询

**参与者**：

- 主参与者：持卡客户
- 辅助参与者：ATM 设备、中央计算机、分行计算机

**前置条件**：

- 客户已通过身份认证
- 账户状态正常

**主流程**：

1. 客户选择"余额查询"功能
2. ATM 发送查询请求到中央计算机
3. 中央计算机路由到分行计算机
4. 分行计算机查询账户余额
5. 分行计算机返回余额信息
6. 中央计算机转发结果到 ATM
7. ATM 显示账户余额
8. 客户确认查看完毕
9. 返回主菜单

**异常流程**：

- **E1**：网络超时
  - 重试 2 次
  - 仍失败则显示"查询失败，请稍后重试"
- **E2**：账户状态异常
  - 显示"账户状态异常，请联系银行"

**后置条件**：

- 客户已查看账户余额
- 交易记录已保存

**用例关系**：

- 包含：UC-ATM-01（持卡认证）

#### UC-ATM-03：现金取款

**参与者**：

- 主参与者：持卡客户
- 辅助参与者：ATM 设备、中央计算机、分行计算机

**前置条件**：

- 客户已通过身份认证
- 账户状态正常
- ATM 有足够现金
- 账户余额充足

**主流程**：

1. 客户选择"取款"功能
2. 系统显示快捷金额选项（100、200、500、1000、2000、5000）
3. 客户选择金额或选择"其他金额"
4. 如果选择其他金额：
   - 客户输入取款金额
   - 系统验证金额格式（100 的倍数）
5. 系统验证取款限额（单笔 ≤5000，日累计 ≤20000）
6. ATM 发送取款请求到中央计算机
7. 中央计算机路由到分行计算机
8. 分行计算机验证余额并锁定金额
9. 分行计算机返回授权结果
10. 如果授权成功：
    - ATM 出钞
    - 客户取走现金
    - ATM 打印交易凭条
    - 分行计算机完成扣款
    - 显示交易成功
11. 返回主菜单

**异常流程**：

- **E1**：金额不是 100 的倍数
  - 显示"请输入 100 的倍数"
  - 返回金额输入步骤
- **E2**：超过单笔限额
  - 显示"单笔取款限额 5000 元，请重新输入"
  - 返回金额输入步骤
- **E3**：超过日累计限额
  - 显示"今日取款已达限额，请明日再试"
  - 返回主菜单
- **E4**：余额不足
  - 显示"余额不足，可用余额：XXX 元"
  - 询问是否调整金额
- **E5**：ATM 现金不足
  - 显示"ATM 现金不足，请选择其他金额或换台机器"
  - 返回金额选择步骤
- **E6**：出钞失败
  - 记录异常日志
  - 显示"出钞异常，请联系银行"
  - 不扣款，返回主菜单
- **E7**：网络超时
  - 重试 3 次
  - 仍失败则取消交易，显示"交易失败，请稍后重试"

**后置条件**：

- 账户余额减少（成功时）
- 交易记录已保存
- ATM 现金库存减少（成功时）
- 客户获得现金和凭条（成功时）

**用例关系**：

- 包含：UC-ATM-01（持卡认证）
- 扩展：打印凭条（可选）

#### UC-TELLER-01：开户

**参与者**：

- 主参与者：柜员
- 辅助参与者：储户、柜员终端、分行计算机

**前置条件**：

- 柜员已登录系统
- 储户提供有效身份证件
- 储户满足开户条件

**主流程**：

1. 储户到柜台申请开户
2. 柜员验证储户身份证件
3. 柜员在终端选择"开户"功能
4. 柜员录入储户基本信息（姓名、身份证号、联系方式、地址）
5. 系统生成账户号码
6. 储户设置初始密码
7. 柜员录入开户金额（如适用）
8. 系统创建账户记录
9. 柜员打印开户凭证
10. 储户签字确认
11. 开户完成

**异常流程**：

- **E1**：身份证件无效
  - 拒绝开户申请
- **E2**：储户信息重复
  - 提示"该身份证已开户"
- **E3**：系统故障
  - 记录故障信息
  - 告知储户稍后办理

**后置条件**：

- 新账户已创建
- 储户获得账户信息
- 开户记录已保存

### 用例关系图

```
持卡客户 --|> 储户
    |
    |-- 持卡认证
    |-- 余额查询
    |-- 现金取款

柜员 --|> 系统管理员
    |
    |-- 开户
    |-- 现金存款
    |-- 支票存款
    |-- 柜台取款

系统管理员
    |
    |-- ATM状态监控
    |-- 补钞管理
    |-- 故障处理
```
