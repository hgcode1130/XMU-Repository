// ========== 服务单状态定义（符合状态图） ==========
// 状态图: 0-PENDING_REVIEW → 1-PENDING_CONFIRM → 2-RECEIVED → 3-ASSIGNED →
//        4-ITEM_RECEIVED(寄修) / 5-ON_SITE(上门) → 6-COMPLETED
//        可从多个状态转到 7-RETURNED(已退回) 或 8-CANCELLED(已取消)
const ORDER_FILTERS = [
  { id: "pending_confirm", label: "待接受" },
  { id: "received", label: "已接受" },
  { id: "assigned", label: "已派工" },
  { id: "item_received", label: "已收件" },
  { id: "on_site", label: "已上门" },
  { id: "completed", label: "已完成" },
  { id: "returned", label: "已退回" },
  { id: "cancelled", label: "已取消" },
];

const ORDER_STATUS_META = {
  pending_review: { label: "待商户审核", className: "tag tag--info" },
  pending_confirm: { label: "待接受", className: "tag tag--warning" },
  received: { label: "已接受", className: "tag tag--info" },
  assigned: { label: "已派工", className: "tag tag--warning" },
  item_received: { label: "已收件", className: "tag tag--info" },
  on_site: { label: "已上门", className: "tag tag--info" },
  completed: { label: "已完成", className: "tag tag--success" },
  returned: { label: "已退回", className: "tag tag--warning" },
  cancelled: { label: "已取消", className: "tag tag--danger" },
};

// ========== 服务合同状态定义（符合状态图） ==========
// 状态图: 0-PENDING_CONFIRM → 1-EFFECTIVE ↔ 2-SUSPENDED
//        可从 PENDING_CONFIRM 转到 4-REJECTED
//        可从 EFFECTIVE/SUSPENDED 转到 3-CANCELLED
//        EFFECTIVE 可自动转到 5-EXPIRED
const CONTRACT_STATUS_META = {
  pending: { label: "待确认", className: "tag tag--info" },
  active: { label: "生效中", className: "tag tag--success" },
  suspended: { label: "已暂停", className: "tag tag--warning" },
  rejected: { label: "已拒绝", className: "tag tag--danger" },
  cancelled: { label: "已取消", className: "tag tag--danger" },
  expired: { label: "已到期", className: "tag tag--info" },
};

const TOAST_DURATION = 3200;

const state = {
  currentRoute: "dashboard",
  ordersFilter: "pending_confirm",
  ordersSearch: "",
  ordersWaybillSearch: "", // 新增：快递单号搜索
  selectedOrderId: null,
  orders: [],
  contracts: [],
  contractView: "pending",
  contractFilters: {
    provider: "盛唐维修服务有限公司",
    serviceName: "",
    regions: [],
    startDate: "",
    endDate: "",
  },
  selectedContractId: null,
  account: {},
  team: [],
  teamSearch: "",
  teamStatusFilter: "all",
  teamRoleFilter: "all",
  notifications: [],
  dashboard: {},
  isAuthenticated: false,
  authView: "login",
};

const els = {
  authContainer: document.getElementById("auth-container"),
  appShell: document.getElementById("app-shell"),
  loginView: document.getElementById("login-view"),
  signupView: document.getElementById("signup-view"),
  sections: document.querySelectorAll(".section"),
  navItems: document.querySelectorAll(".nav-item[data-route]"),
  ordersFilters: document.getElementById("orders-filters"),
  ordersSearch: document.getElementById("orders-search"),
  ordersReset: document.getElementById("orders-reset"),
  ordersTableBody: document.getElementById("orders-table-body"),
  ordersEmpty: document.getElementById("orders-empty"),
  ordersAlert: document.getElementById("orders-alert"),
  contractStatusTabs: document.querySelector("[data-contract-status-tabs]"),
  contractFilterForm: document.querySelector("[data-contract-filter-form]"),
  contractList: document.querySelector("[data-contract-list]"),
  contractEmpty: document.querySelector("[data-contract-empty]"),
  dashboardSummary: document.getElementById("dashboard-summary"),
  dashboardActivity: document.getElementById("dashboard-activity"),
  accountAlert: document.getElementById("account-alert"),
  accountTabs: document.getElementById("account-tabs"),
  accountCompany: document.getElementById("account-company"),
  accountRegions: document.getElementById("account-regions"),
  accountFiles: document.getElementById("account-files"),
  teamTableBody: document.getElementById("team-table-body"),
  teamSearch: document.getElementById("team-search"),
  teamStatusFilter: document.getElementById("team-status-filter"),
  teamRoleFilter: document.getElementById("team-role-filter"),
  teamReset: document.getElementById("team-reset"),
  teamEmpty: document.getElementById("team-empty"),
  notificationsList: document.getElementById("notifications-list"),
  toastContainer: document.getElementById("toast-container"),
  modal: document.getElementById("modal"),
  modalTitle: document.getElementById("modal-title"),
  modalBody: document.getElementById("modal-body"),
  modalConfirm: document.getElementById("modal-confirm"),
  modalCancel: document.getElementById("modal-cancel"),
  loginForm: document.getElementById("auth-login-form"),
  loginAccount: document.getElementById("auth-login-account"),
  loginPassword: document.getElementById("auth-login-password"),
  signupForm: document.getElementById("auth-signup-form"),
  signupDraft: document.getElementById("auth-signup-draft"),
  authShowSignup: document.querySelectorAll('[data-auth="show-signup"]'),
  authShowLogin: document.querySelectorAll('[data-auth="show-login"]'),
};

let modalConfirmHandler = null;
let loginInitialized = false;
let signupInitialized = false;

function initData() {
  // ========== 服务单数据（符合状态图的完整状态） ==========
  state.orders = [
    {
      id: "SO-2201",
      merchant: "品优家电",
      serviceType: "寄修",
      serviceCategory: "家电维修",
      region: "上海 徐汇",
      createdAt: "2025-10-14 09:23",
      status: "pending_confirm", // 待接受
      requireReceipt: true,
      received: false,
      priority: "高",
      waybillNumber: "", // 快递单号
      customer: {
        name: "王女士",
        phone: "138****2210",
        address: "上海市徐汇区虹桥路 218 号",
      },
      product: '海信 75" 智能电视',
      notes: "机器无法开机，客户希望加急处理",
      assignedTo: null,
      expectedFinish: "2025-10-16 18:00",
      timeline: [
        { time: "2025-10-14 09:20", text: "顾客提交售后申请", actor: "顾客" },
        {
          time: "2025-10-14 09:22",
          text: "商户审核通过，创建服务单",
          actor: "品优家电",
        },
        { time: "2025-10-14 09:23", text: "服务单派发给服务商", actor: "系统" },
      ],
    },
    {
      id: "SO-2200",
      merchant: "悦选商城",
      serviceType: "上门安装",
      serviceCategory: "家电安装",
      region: "杭州 西湖",
      createdAt: "2025-10-13 16:48",
      status: "on_site", // 已上门
      requireReceipt: false,
      received: true,
      priority: "中",
      waybillNumber: "",
      customer: {
        name: "张先生",
        phone: "138****8820",
        address: "浙江省杭州市西湖区南山路 88 号",
      },
      product: '海信 75" 智能电视',
      notes: "需墙体加固，携带钻孔工具",
      assignedTo: "李工",
      expectedFinish: "2025-10-16 18:00",
      timeline: [
        { time: "2025-10-13 16:48", text: "商户提交服务单", actor: "悦选商城" },
        { time: "2025-10-13 17:15", text: "服务商接受服务单", actor: "王主管" },
        {
          time: "2025-10-14 09:00",
          text: "指派维修师傅：李工",
          actor: "王主管",
        },
        { time: "2025-10-14 14:30", text: "维修师傅上门签到", actor: "李工" },
      ],
    },
    {
      id: "SO-2199",
      merchant: "智享数码",
      serviceType: "寄修",
      serviceCategory: "数码维修",
      region: "南京 建邺",
      createdAt: "2025-10-12 11:05",
      status: "completed", // 已完成
      requireReceipt: true,
      received: true,
      priority: "中",
      waybillNumber: "SF1234567890",
      customer: {
        name: "赵女士",
        phone: "137****1190",
        address: "江苏省南京市建邺区江东中路 88 号",
      },
      product: "戴森 无线吸尘器",
      notes: "需更换电池组",
      assignedTo: "陈工",
      expectedFinish: "2025-10-13 12:00",
      timeline: [
        { time: "2025-10-12 11:05", text: "商户提交服务单", actor: "智享数码" },
        { time: "2025-10-12 12:10", text: "服务商接受服务单", actor: "王主管" },
        {
          time: "2025-10-12 14:00",
          text: "指派维修师傅：陈工",
          actor: "王主管",
        },
        {
          time: "2025-10-12 15:20",
          text: "确认收件，快递单号 SF1234567890",
          actor: "陈工",
        },
        { time: "2025-10-13 10:15", text: "完成维修并寄回", actor: "陈工" },
      ],
    },
    {
      id: "SO-2198",
      merchant: "极客家居",
      serviceType: "上门维护",
      serviceCategory: "净水设备维护",
      region: "苏州 工业园区",
      createdAt: "2025-10-12 08:33",
      status: "assigned", // 已派工
      requireReceipt: false,
      received: false,
      priority: "高",
      waybillNumber: "",
      customer: {
        name: "刘先生",
        phone: "186****3345",
        address: "江苏省苏州市工业园区独墅湖大道 88 号",
      },
      product: "沁园 RO 净水器",
      notes: "滤芯更换，客户预约 15 日下午",
      assignedTo: "赵工",
      expectedFinish: "2025-10-15 18:00",
      timeline: [
        { time: "2025-10-12 08:33", text: "商户提交服务单", actor: "极客家居" },
        { time: "2025-10-12 09:00", text: "服务商接受服务单", actor: "王主管" },
        {
          time: "2025-10-13 09:40",
          text: "指派维修师傅：赵工",
          actor: "王主管",
        },
      ],
    },
    {
      id: "SO-2196",
      merchant: "品优家电",
      serviceType: "寄修",
      serviceCategory: "家电维修",
      region: "上海 浦东",
      createdAt: "2025-10-11 14:20",
      status: "item_received", // 已收件
      requireReceipt: true,
      received: true,
      priority: "中",
      waybillNumber: "YT9876543210",
      customer: {
        name: "李先生",
        phone: "139****5566",
        address: "上海市浦东新区陆家嘴环路 100 号",
      },
      product: "美的 空调",
      notes: "制冷效果差，需检修",
      assignedTo: "陈工",
      expectedFinish: "2025-10-14 18:00",
      timeline: [
        { time: "2025-10-11 14:20", text: "商户提交服务单", actor: "品优家电" },
        { time: "2025-10-11 15:00", text: "服务商接受服务单", actor: "王主管" },
        {
          time: "2025-10-11 16:00",
          text: "指派维修师傅：陈工",
          actor: "王主管",
        },
        {
          time: "2025-10-12 10:30",
          text: "确认收件，快递单号 YT9876543210",
          actor: "陈工",
        },
      ],
    },
    {
      id: "SO-2195",
      merchant: "悦选商城",
      serviceType: "寄修",
      serviceCategory: "数码维修",
      region: "杭州 滨江",
      createdAt: "2025-10-10 09:15",
      status: "returned", // 已退回
      requireReceipt: true,
      received: true,
      priority: "低",
      waybillNumber: "SF0011223344",
      customer: {
        name: "吴女士",
        phone: "136****7788",
        address: "浙江省杭州市滨江区网商路 599 号",
      },
      product: "苹果 iPad",
      notes: "屏幕碎裂，检查后发现人为损坏，退回",
      assignedTo: "陈工",
      expectedFinish: null,
      timeline: [
        { time: "2025-10-10 09:15", text: "商户提交服务单", actor: "悦选商城" },
        { time: "2025-10-10 10:00", text: "服务商接受服务单", actor: "王主管" },
        {
          time: "2025-10-10 11:00",
          text: "指派维修师傅：陈工",
          actor: "王主管",
        },
        {
          time: "2025-10-11 09:00",
          text: "确认收件，快递单号 SF0011223344",
          actor: "陈工",
        },
        {
          time: "2025-10-11 14:00",
          text: "检查发现人为损坏，不在保修范围，退回服务单",
          actor: "陈工",
        },
      ],
    },
    {
      id: "SO-2197",
      merchant: "安心家电",
      serviceType: "寄修",
      serviceCategory: "家电维修",
      region: "成都 高新",
      createdAt: "2025-10-11 10:20",
      status: "cancelled", // 已取消
      requireReceipt: true,
      received: false,
      priority: "低",
      waybillNumber: "",
      customer: {
        name: "周女士",
        phone: "135****9981",
        address: "四川省成都市高新区天府大道 188 号",
      },
      product: "松下 洗衣机",
      notes: "客户取消，原因：自行解决",
      assignedTo: null,
      expectedFinish: null,
      timeline: [
        { time: "2025-10-11 10:20", text: "商户提交服务单", actor: "安心家电" },
        {
          time: "2025-10-11 11:15",
          text: "客户取消服务单，原因：自行解决",
          actor: "客户",
        },
        { time: "2025-10-11 11:16", text: "服务商确认撤销", actor: "王主管" },
      ],
    },
    {
      id: "SO-2194",
      merchant: "智享数码",
      serviceType: "寄修",
      serviceCategory: "数码维修",
      region: "南京 鼓楼",
      createdAt: "2025-10-09 16:30",
      status: "received", // 已接受（待派工）
      requireReceipt: true,
      received: false,
      priority: "中",
      waybillNumber: "",
      customer: {
        name: "孙先生",
        phone: "137****2233",
        address: "江苏省南京市鼓楼区中山北路 200 号",
      },
      product: "索尼 相机",
      notes: "快门故障，需检修",
      assignedTo: null,
      expectedFinish: "2025-10-12 18:00",
      timeline: [
        { time: "2025-10-09 16:30", text: "商户提交服务单", actor: "智享数码" },
        { time: "2025-10-09 17:00", text: "服务商接受服务单", actor: "王主管" },
      ],
    },
  ];

  state.selectedOrderId = state.orders[0].id;

  state.contracts = [
    {
      id: "SC-2025-001",
      code: "SC-2025-001",
      status: "pending",
      serviceName: "电视挂壁安装标准版",
      merchantName: "品优家电",
      providerName: "盛唐维修服务有限公司",
      regions: ["长三角", "华东"],
      products: ["壁挂电视安装套件", "墙体加固服务"],
      serviceItems: ["上门勘察", "挂架安装", "线缆隐藏", "试运行"],
      serviceContent:
        "提供 65-86 英寸电视的挂壁安装，包含墙体勘察、挂架固定、线路收纳与调试。",
      startDate: "2025-11-01",
      endDate: "2026-10-31",
      contactName: "刘经理",
      contactPhone: "138****2210",
      paymentTerms: "按单结算，月度对账，T+30 支付。",
      breachLiability: "服务未达标需免费返工，并赔偿由此产生的损失。",
      attachments: [
        { name: "服务合同正文.pdf", type: "pdf" },
        { name: "服务范围说明.docx", type: "doc" },
      ],
      clauses: [
        {
          title: "服务范围",
          content: "提供挂壁安装、线路整理、试运行与客户培训。",
        },
        {
          title: "服务标准",
          content: "预约响应≤2小时，上门服务≤48小时，单次服务 60 分钟内完成。",
        },
        {
          title: "结算方式",
          content: "每单 199 元，月度对账，逾期支付按银行同期利率收取违约金。",
        },
      ],
      timeline: [
        {
          time: "2025-10-24 10:20",
          actor: "品优家电",
          text: "发起合同签署请求并上传条款附件。",
        },
        {
          time: "2025-10-24 11:05",
          actor: "系统",
          text: "待服务商确认合同内容。",
        },
      ],
      rejectionHistory: [],
      lastUpdatedAt: "2025-10-24 11:05",
      suspensionHistory: [],
    },
    {
      id: "SC-2025-002",
      code: "SC-2025-002",
      status: "pending",
      serviceName: "冰箱寄修保养套餐",
      merchantName: "悦选商城",
      providerName: "盛唐维修服务有限公司",
      regions: ["长三角", "华南"],
      products: ["冰箱寄修", "冷凝器清洗"],
      serviceItems: ["寄修收件", "故障检测", "备件更换", "保养清洁"],
      serviceContent:
        "提供冰箱寄修及保养服务，48 小时内出具检测报告，支持加急通道。",
      startDate: "2025-10-28",
      endDate: "2026-10-27",
      contactName: "张主管",
      contactPhone: "137****8899",
      paymentTerms: "按件计费，每件 149 元，季度对账。",
      breachLiability: "逾期未完成需退还费用并赔偿 30% 服务金额。",
      attachments: [
        { name: "寄修服务条款.pdf", type: "pdf" },
        { name: "收费标准.xlsx", type: "xlsx" },
      ],
      clauses: [
        {
          title: "寄修流程",
          content: "商户下单后 2 小时内响应，24 小时内收件并登记。",
        },
        {
          title: "备件保障",
          content: "使用原厂或认证备件，保修期 90 天。",
        },
        {
          title: "售后支持",
          content: "提供 7x12 小时热线支持与在线工单反馈。",
        },
      ],
      timeline: [
        {
          time: "2025-10-25 09:10",
          actor: "悦选商城",
          text: "提交合同草稿并指定生效日期。",
        },
        {
          time: "2025-10-25 09:12",
          actor: "系统",
          text: "提醒服务商审核合同条款。",
        },
      ],
      rejectionHistory: [],
      lastUpdatedAt: "2025-10-25 09:12",
      suspensionHistory: [],
    },
    {
      id: "SC-2024-118",
      code: "SC-2024-118",
      status: "active",
      serviceName: "空调深度保养套餐",
      merchantName: "智选家电",
      providerName: "盛唐维修服务有限公司",
      regions: ["华东", "华南"],
      products: ["挂机空调", "中央空调"],
      serviceItems: ["室内机拆洗", "室外机高压冲洗", "制冷性能测试"],
      serviceContent:
        "为家用与商用空调提供深度保养，含滤网更换、冷凝管清洁、性能校准。",
      startDate: "2024-08-01",
      endDate: "2025-07-31",
      contactName: "王主管",
      contactPhone: "136****7788",
      paymentTerms: "按单 299 元，月度结算；季度完成度低于 95% 则扣减 5%。",
      breachLiability: "未按约定时间提供服务需承担单次服务费用 150% 的违约金。",
      attachments: [
        { name: "空调保养服务合同.pdf", type: "pdf" },
        { name: "服务 SLA.png", type: "img" },
      ],
      clauses: [
        {
          title: "预约规则",
          content: "支持 T+1 预约，旺季需提前 3 天提交需求。",
        },
        {
          title: "质量保障",
          content: "如出现返修，48 小时内免费上门整改。",
        },
        {
          title: "费用调整",
          content: "市场价格波动超过 10% 时双方协商调价。",
        },
      ],
      timeline: [
        {
          time: "2024-07-20 14:10",
          actor: "智选家电",
          text: "发起合同签署并附带 SLA 文档。",
        },
        {
          time: "2024-07-21 09:32",
          actor: "盛唐维修",
          text: "确认合同并约定生效日期。",
        },
        {
          time: "2024-08-01 00:00",
          actor: "系统",
          text: "合同已生效，可接收服务单。",
        },
        {
          time: "2025-05-15 16:20",
          actor: "系统",
          text: "更新：完成半年度服务绩效评估。",
        },
      ],
      rejectionHistory: [],
      lastUpdatedAt: "2025-05-15 16:20",
      suspensionHistory: [],
    },
    {
      id: "SC-2024-210",
      code: "SC-2024-210",
      status: "suspended",
      serviceName: "智能家居安装保养",
      merchantName: "优品生活馆",
      providerName: "盛唐维修服务有限公司",
      regions: ["华东", "华北"],
      products: ["智能灯控安装", "智能锁维护"],
      serviceItems: ["上门安装", "远程调试", "定期巡检"],
      serviceContent:
        "提供智能家居设备的安装及运维服务，包含硬件调试与远程监控策略配置。",
      startDate: "2024-05-01",
      endDate: "2025-04-30",
      contactName: "赵经理",
      contactPhone: "139****1201",
      paymentTerms: "年度维护费 48000 元，按季度分摊结算。",
      breachLiability: "未按时提供巡检需退还当季费用，并承担 20% 违约金。",
      attachments: [
        { name: "智能家居运维合同.pdf", type: "pdf" },
        { name: "巡检SLA.xlsx", type: "xlsx" },
      ],
      clauses: [
        {
          title: "巡检频率",
          content: "每季度至少一次现场巡检，并提供报告。",
        },
        {
          title: "远程支持",
          content: "提供 7x24 小时远程监控支持，异常 2 小时内响应。",
        },
      ],
      timeline: [
        {
          time: "2024-04-18 09:20",
          actor: "优品生活馆",
          text: "提交合同签署申请。",
        },
        {
          time: "2024-04-20 15:00",
          actor: "盛唐维修",
          text: "确认合同并设定巡检周期。",
        },
        {
          time: "2025-09-15 10:30",
          actor: "盛唐维修",
          text: "提交暂停申请，原因：等待商户调整结算流程。",
        },
      ],
      rejectionHistory: [],
      suspensionHistory: [
        {
          time: "2025-09-15 10:30",
          actor: "盛唐维修",
          reason: "等待商户调整结算流程",
        },
      ],
      lastUpdatedAt: "2025-09-15 10:30",
    },
    {
      id: "SC-2023-071",
      code: "SC-2023-071",
      status: "expired",
      serviceName: "洗衣机延保服务",
      merchantName: "安心家电",
      providerName: "盛唐维修服务有限公司",
      regions: ["华北"],
      products: ["洗衣机延保套餐"],
      serviceItems: ["延保登记", "上门维修", "备件更换"],
      serviceContent:
        "为指定品牌洗衣机提供延保期内的维修与备件支持，支持 24 小时内响应。",
      startDate: "2023-03-01",
      endDate: "2024-02-29",
      contactName: "李主管",
      contactPhone: "139****6677",
      paymentTerms: "预付 50% 保证金，按季度结算实际服务量。",
      breachLiability:
        "若服务无法满足 SLA，需退还剩余保证金并承担 20% 违约金。",
      attachments: [{ name: "延保合同归档.zip", type: "zip" }],
      clauses: [
        {
          title: "附件保管",
          content: "所有维修凭证需在 7 日内上传至平台存档。",
        },
        {
          title: "终止条款",
          content: "任一方违约或未达成 KPI，可提前 30 日书面通知终止。",
        },
      ],
      timeline: [
        {
          time: "2023-02-18 09:00",
          actor: "安心家电",
          text: "发起延保合同签署。",
        },
        {
          time: "2023-02-19 10:15",
          actor: "盛唐维修",
          text: "确认合同并约定 KPI。",
        },
        {
          time: "2024-02-29 23:59",
          actor: "系统",
          text: "合同到期未续签，自动终止。",
        },
      ],
      rejectionHistory: [
        {
          time: "2023-05-10 11:20",
          actor: "盛唐维修",
          reason: "商户未按时结算二季度费用，已提醒补齐。",
        },
      ],
      terminationHistory: [
        {
          time: "2024-02-29 23:59",
          actor: "系统",
          reason: "合同到期未续签，自动终止。",
        },
      ],
      lastUpdatedAt: "2024-02-29 23:59",
      suspensionHistory: [],
    },
  ];

  state.account = {
    pendingMessage: '您于 2025-10-12 提交的"服务地区变更"申请正在审核中',
    company: {
      id: "SP-88901",
      name: "盛唐维修服务有限公司",
      category: "家电维修",
      contact: "王主管 · 138****8890",
      address: "上海市浦东新区张江高科技园区 288 号",
      serviceHours: "周一至周日 08:00-21:00",
      businessLicense: "营业执照.pdf",
      serviceProducts: "电视机、洗衣机、冰箱、空调",
    },
    regions: [
      { name: "上海市 全域", status: "active" },
      { name: "浙江省 杭州", status: "pending" },
    ],
    files: [
      { name: "营业执照.pdf", status: "approved" },
      { name: "服务能力认证.jpg", status: "approved" },
      { name: "寄修仓储证明.pdf", status: "pending" },
    ],
  };

  state.team = [
    {
      id: "T-001",
      name: "王主管",
      contact: "138****8890",
      role: "管理员",
      status: "active",
    },
    {
      id: "T-002",
      name: "李工",
      contact: "137****2210",
      role: "维修师傅",
      status: "paused",
    },
    {
      id: "T-003",
      name: "赵工",
      contact: "136****5432",
      role: "维修师傅",
      status: "active",
    },
    {
      id: "T-004",
      name: "陈工",
      contact: "139****7770",
      role: "维修师傅",
      status: "active",
    },
  ];

  state.notifications = [
    {
      id: "N-001",
      type: "danger",
      text: "服务单 #SO-2201 已等待超过 2 小时",
      route: "orders",
      read: false,
    },
    {
      id: "N-002",
      type: "success",
      text: "账户信息变更申请审核结果：已通过",
      route: "account",
      read: true,
    },
    {
      id: "N-003",
      type: "info",
      text: "商户「悦选商城」留言：请在 10 月 15 日前完成安装",
      route: "orders",
      read: false,
    },
  ];

  state.dashboard = {
    metrics: [
      {
        label: "待我处理",
        id: "pending",
        chips: ["可接服务单", "待派工", "待收件"],
        actionRoute: "orders",
      },
      {
        label: "本周完成服务单",
        id: "completed",
        chips: ["平均处理时长", "加急订单"],
      },
      {
        label: "服务满意度",
        id: "satisfaction",
        chips: ["新增好评", "需回访"],
      },
    ],
    activities: [
      {
        text: "服务单 #SO-2198 即将超时，请尽快派工。",
        type: "warning",
        action: { label: "立即处理", route: "orders" },
      },
      { text: "账户信息变更申请已通过审核。", type: "success" },
      {
        text: "商户「品优家电」新增寄修服务单 #SO-2201。",
        type: "info",
        action: { label: "接受服务单", route: "orders" },
      },
    ],
  };
}

function activateRoute(route) {
  state.currentRoute = route;
  els.sections.forEach((section) => {
    section.classList.toggle("active", section.dataset.section === route);
  });
  els.navItems.forEach((item) => {
    item.classList.toggle("active", item.dataset.route === route);
  });
  renderByRoute(route);
}

function renderByRoute(route) {
  switch (route) {
    case "dashboard":
      renderDashboard();
      break;
    case "orders":
      renderOrders();
      break;
    case "contracts":
      renderContracts();
      break;
    case "team":
      renderTeam();
      break;
    case "account":
      renderAccount();
      break;
    case "notifications":
      renderNotifications();
      break;
    default:
      renderDashboard();
  }
}

function renderDashboard() {
  const summary = state.dashboard.metrics.map((metric) => {
    if (metric.id === "pending") {
      const available = state.orders.filter(
        (order) => order.status === "available"
      ).length;
      const needAssignment = state.orders.filter(
        (order) => order.status === "in_progress" && !order.received
      ).length;
      const needReceipt = state.orders.filter(
        (order) =>
          order.requireReceipt &&
          !order.received &&
          order.status === "in_progress"
      ).length;
      return {
        ...metric,
        value: available + needAssignment + needReceipt,
        chips: [
          `${available} 个待接受`,
          `${needAssignment} 个待派工`,
          `${needReceipt} 个待收件`,
        ],
      };
    }
    if (metric.id === "completed") {
      const completed = state.orders.filter(
        (order) => order.status === "completed"
      ).length;
      return {
        ...metric,
        value: completed,
        chips: ["平均处理 4.6 小时", "加急订单 3 单"],
      };
    }
    if (metric.id === "satisfaction") {
      return {
        ...metric,
        value: "4.8 ★",
        chips: ["新增好评 5 条", "需回访 2 条"],
      };
    }
    return metric;
  });

  els.dashboardSummary.innerHTML = summary
    .map(
      (item) => `
      <div class="card" data-route="${item.actionRoute || ""}">
        <div class="card__label">${item.label}</div>
        <div class="card__value">${item.value}</div>
        <div class="chip-row">
          ${item.chips
            .map((chip) => `<span class="chip">${chip}</span>`)
            .join("")}
        </div>
      </div>`
    )
    .join("");

  els.dashboardSummary.querySelectorAll(".card[data-route]").forEach((card) => {
    card.addEventListener("click", () => {
      const route = card.dataset.route;
      if (route) activateRoute(route);
    });
  });

  els.dashboardActivity.innerHTML = state.dashboard.activities
    .map((activity) => {
      const typeClass =
        activity.type === "warning"
          ? "tag tag--warning"
          : activity.type === "success"
          ? "tag tag--success"
          : "tag tag--info";
      return `
        <div class="list-item">
          <span>${activity.text}</span>
          <div class="table-actions">
            <span class="${typeClass}">${
        activity.type === "warning"
          ? "提醒"
          : activity.type === "success"
          ? "成功"
          : "通知"
      }</span>
            ${
              activity.action
                ? `<button class="btn btn--ghost" data-route="${activity.action.route}">${activity.action.label}</button>`
                : ""
            }
          </div>
        </div>`;
    })
    .join("");
}

function showAuth(view) {
  state.authView = view;
  if (els.loginView && els.signupView) {
    if (view === "login") {
      els.loginView.classList.remove("hidden");
      els.signupView.classList.add("hidden");
    } else {
      els.signupView.classList.remove("hidden");
      els.loginView.classList.add("hidden");
    }
  }
}

function renderLogin() {
  if (!loginInitialized && els.loginForm) {
    els.loginForm.addEventListener("submit", (event) => {
      event.preventDefault();
      const account = els.loginAccount.value.trim();
      if (!account) {
        showToast("请输入登录账号", "error");
        return;
      }
      state.isAuthenticated = true;
      showToast("登录成功，正在跳转控制台", "success");
      if (els.authContainer && els.appShell) {
        els.authContainer.classList.add("hidden");
        els.appShell.classList.remove("hidden");
      }
      activateRoute("dashboard");
    });
    loginInitialized = true;
  }
}

function renderSignup() {
  if (!signupInitialized && els.signupForm) {
    const form = els.signupForm;
    const draftBtn = els.signupDraft;

    function clearSignupErrors() {
      form
        .querySelectorAll(".form-field")
        .forEach((field) => field.classList.remove("error"));
    }

    function validateSignup() {
      const data = new FormData(form);
      const required = [
        "company",
        "category",
        "products",
        "address",
        "contact",
        "email",
        "coverage",
        "account",
        "password",
        "confirm",
      ];
      const errors = [];
      required.forEach((key) => {
        const value = data.get(key);
        if (!value || !value.trim()) errors.push(key);
      });
      const phone = data.get("contact");
      if (phone && !/^1\\d{10}$/.test(phone)) errors.push("contact");
      const password = data.get("password");
      if (password && password.length < 8) errors.push("password");
      if (password !== data.get("confirm")) errors.push("confirm");
      if (!form.querySelector('[name="agreements"]').checked)
        errors.push("agreements");

      clearSignupErrors();
      errors.forEach((key) => {
        if (key === "agreements") {
          showToast("提交前请勾选协议", "error");
        } else {
          const field = form.querySelector(`[data-signup-field=\"${key}\"]`);
          if (field) field.classList.add("error");
        }
      });
      if (errors.length) {
        showToast("请完善注册信息", "error");
        return null;
      }
      return Object.fromEntries(data.entries());
    }

    form.addEventListener("submit", (event) => {
      event.preventDefault();
      const payload = validateSignup();
      if (!payload) return;
      showToast("注册申请已提交，预计 1-3 个工作日内审核", "success");
      form.reset();
      clearSignupErrors();
      showAuth("login");
    });

    if (draftBtn) {
      draftBtn.addEventListener("click", () => {
        const payload = validateSignup();
        if (!payload) return;
        showToast("草稿已保存，可稍后继续完善", "info");
      });
    }

    signupInitialized = true;
  }
}

function renderOrders() {
  renderOrderFilters();
  const filtered = state.orders.filter((order) => {
    const statusMatch = order.status === state.ordersFilter;
    const searchMatch = state.ordersSearch
      ? [order.id, order.merchant, order.serviceType, order.region].some(
          (field) => field.includes(state.ordersSearch)
        )
      : true;
    return statusMatch && searchMatch;
  });

  // 统计待处理的服务单
  const pendingConfirmCount = state.orders.filter(
    (o) => o.status === "pending_confirm"
  ).length;
  const assignedNeedReceiptCount = state.orders.filter(
    (o) => o.status === "assigned" && o.requireReceipt && !o.received
  ).length;

  let alertText = "";
  if (pendingConfirmCount > 0) {
    alertText += `${pendingConfirmCount} 个待接受`;
  }
  if (assignedNeedReceiptCount > 0) {
    alertText +=
      (alertText ? "，" : "") + `${assignedNeedReceiptCount} 个待收件`;
  }
  els.ordersAlert.textContent = alertText
    ? `当前有 ${alertText} 的服务单`
    : "当前所有服务单均已处理";
  els.ordersAlert.classList.toggle("hidden", !alertText);

  if (!filtered.length) {
    els.ordersTableBody.innerHTML = "";
    els.ordersEmpty.classList.remove("hidden");
    return;
  }
  els.ordersEmpty.classList.add("hidden");

  els.ordersTableBody.innerHTML = filtered
    .map((order) => {
      const meta = ORDER_STATUS_META[order.status] || {
        label: "未知",
        className: "tag tag--info",
      };
      const actions = [];

      // 根据状态图定义操作按钮
      switch (order.status) {
        case "pending_confirm":
          // 待接受：可接受或拒绝
          actions.push(
            `<button class="btn btn--primary" data-action="order-accept" data-order="${order.id}">接受</button>`
          );
          actions.push(
            `<button class="btn btn--danger" data-action="order-reject" data-order="${order.id}">拒绝</button>`
          );
          break;
        case "received":
          // 已接受：可派工或取消
          actions.push(
            `<button class="btn btn--primary" data-action="order-assign" data-order="${order.id}">派工</button>`
          );
          actions.push(
            `<button class="btn btn--ghost" data-action="order-cancel" data-order="${order.id}">取消</button>`
          );
          break;
        case "assigned":
          // 已派工：可确认收件(寄修)/上门签到(上门)/退回/取消
          if (order.requireReceipt) {
            actions.push(
              `<button class="btn btn--secondary" data-action="order-receive" data-order="${order.id}">确认收件</button>`
            );
          } else {
            actions.push(
              `<button class="btn btn--secondary" data-action="order-onsite" data-order="${order.id}">上门签到</button>`
            );
          }
          actions.push(
            `<button class="btn btn--warning" data-action="order-return" data-order="${order.id}">退回</button>`
          );
          actions.push(
            `<button class="btn btn--ghost" data-action="order-reassign" data-order="${order.id}">重新派工</button>`
          );
          break;
        case "item_received":
          // 已收件：可完成或退回
          actions.push(
            `<button class="btn btn--primary" data-action="order-complete" data-order="${order.id}">完成服务</button>`
          );
          actions.push(
            `<button class="btn btn--warning" data-action="order-return" data-order="${order.id}">退回</button>`
          );
          break;
        case "on_site":
          // 已上门：可完成或退回
          actions.push(
            `<button class="btn btn--primary" data-action="order-complete" data-order="${order.id}">完成服务</button>`
          );
          actions.push(
            `<button class="btn btn--warning" data-action="order-return" data-order="${order.id}">退回</button>`
          );
          break;
        case "completed":
        case "returned":
        case "cancelled":
          // 终态：只能查看
          break;
      }

      actions.push(
        `<button class="btn btn--ghost" data-action="order-detail" data-order="${order.id}">查看详情</button>`
      );

      return `
        <tr>
          <td>${order.id}</td>
          <td>${order.merchant}</td>
          <td>${order.serviceType}</td>
          <td>${order.region}</td>
          <td>${order.createdAt}</td>
          <td><span class="${meta.className}">${meta.label}</span></td>
          <td class="table-actions">${actions.join("")}</td>
        </tr>`;
    })
    .join("");
}

function renderOrderFilters() {
  els.ordersFilters.innerHTML = ORDER_FILTERS.map((filter) => {
    const count = state.orders.filter(
      (order) => order.status === filter.id
    ).length;
    return `<div class="pill-tabs__item ${
      state.ordersFilter === filter.id ? "active" : ""
    }" data-filter="${filter.id}">${filter.label} (${count})</div>`;
  }).join("");
}

function renderContracts() {
  renderContractStatusTabs();
  renderContractFilters();
  const filtered = getFilteredContracts();
  renderContractList(filtered);
}

function renderContractStatusTabs() {
  if (!els.contractStatusTabs) return;
  const counts = { pending: 0, active: 0, suspended: 0, terminated: 0 };
  state.contracts.forEach((contract) => {
    const bucket = getContractBucket(contract.status);
    counts[bucket] = (counts[bucket] || 0) + 1;
  });

  els.contractStatusTabs
    .querySelectorAll("[data-contract-status]")
    .forEach((button) => {
      const { contractStatus } = button.dataset;
      if (!button.dataset.label) {
        button.dataset.label = button.textContent.trim().replace(/\(.+?\)/, "");
      }
      const baseLabel = button.dataset.label;
      button.textContent = `${baseLabel} (${counts[contractStatus] || 0})`;
      button.classList.toggle("active", state.contractView === contractStatus);
    });
}

function renderContractFilters() {
  if (!els.contractFilterForm) return;
  const form = els.contractFilterForm;
  const { provider, serviceName, regions, startDate, endDate } =
    state.contractFilters;
  const providerInput = form.querySelector('[name="provider"]');
  const serviceNameInput = form.querySelector('[name="serviceName"]');
  const regionsSelect = form.querySelector('[name="regions"]');
  const startDateInput = form.querySelector('[name="startDate"]');
  const endDateInput = form.querySelector('[name="endDate"]');

  if (providerInput) providerInput.value = provider || "";
  if (serviceNameInput) serviceNameInput.value = serviceName || "";
  if (regionsSelect) {
    Array.from(regionsSelect.options).forEach((option) => {
      option.selected = regions.includes(option.value);
    });
  }
  if (startDateInput) startDateInput.value = startDate || "";
  if (endDateInput) endDateInput.value = endDate || "";
}

function getFilteredContracts() {
  const { serviceName, regions, startDate, endDate } = state.contractFilters;
  return state.contracts.filter((contract) => {
    const view = getContractBucket(contract.status);
    if (view !== state.contractView) return false;

    const nameMatch = serviceName
      ? contract.serviceName.includes(serviceName)
      : true;

    const regionMatch = regions.length
      ? regions.some((region) => contract.regions.includes(region))
      : true;

    const startMatch = startDate ? contract.startDate >= startDate : true;
    const endMatch = endDate ? contract.endDate <= endDate : true;

    return nameMatch && regionMatch && startMatch && endMatch;
  });
}

function renderContractList(contracts) {
  if (!els.contractList || !els.contractEmpty) return;
  if (!contracts.length) {
    els.contractList.innerHTML = "";
    els.contractEmpty.classList.remove("hidden");
    if (
      !state.selectedContractId ||
      !state.contracts.some((c) => c.id === state.selectedContractId)
    ) {
      state.selectedContractId = null;
    }
    return;
  }

  els.contractEmpty.classList.add("hidden");
  if (
    !state.selectedContractId ||
    !contracts.some((contract) => contract.id === state.selectedContractId)
  ) {
    state.selectedContractId = contracts[0].id;
  }

  els.contractList.innerHTML = contracts
    .map((contract) => {
      const meta = CONTRACT_STATUS_META[contract.status];
      const regions = contract.regions.join("、");
      const products = contract.products.join("、");
      const selected = contract.id === state.selectedContractId;
      const latestSuspension = getLatestSuspension(contract);
      const actions = [
        `<button class="btn btn--ghost" data-action="contract-open" data-contract="${contract.id}">查看详情</button>`,
      ];

      if (contract.status === "pending") {
        actions.push(
          `<button class="btn btn--primary" data-action="contract-confirm" data-contract="${contract.id}">确认合同</button>`
        );
        actions.push(
          `<button class="btn btn--danger" data-action="contract-reject" data-contract="${contract.id}">拒绝合同</button>`
        );
      } else if (contract.status === "active") {
        actions.push(
          `<button class="btn btn--secondary" data-action="contract-suspend" data-contract="${contract.id}">暂停合同</button>`
        );
        actions.push(
          `<button class="btn btn--danger" data-action="contract-cancel" data-contract="${contract.id}">取消合同</button>`
        );
        actions.push(
          `<button class="btn btn--ghost" data-action="contract-download" data-contract="${contract.id}">下载合同</button>`
        );
      } else if (contract.status === "suspended") {
        actions.push(
          `<button class="btn btn--primary" data-action="contract-restore" data-contract="${contract.id}">恢复合同</button>`
        );
        actions.push(
          `<button class="btn btn--danger" data-action="contract-cancel" data-contract="${contract.id}">取消合同</button>`
        );
        actions.push(
          `<button class="btn btn--ghost" data-action="contract-download" data-contract="${contract.id}">下载合同</button>`
        );
      } else {
        // cancelled, rejected, expired 状态只能下载
        actions.push(
          `<button class="btn btn--ghost" data-action="contract-download" data-contract="${contract.id}">下载合同</button>`
        );
      }

      const suspensionNotice =
        contract.status === "suspended" && latestSuspension
          ? `<div class="contract-card__notice">
              <span class="contracts-detail__label">暂停原因</span>
              <p>${escapeHtml(latestSuspension.reason)} · ${escapeHtml(
              latestSuspension.time
            )}</p>
            </div>`
          : "";

      return `
        <article class="contract-card ${
          selected ? "contract-card--active" : ""
        }" data-contract="${contract.id}">
          <header class="contract-card__header">
            <div>
              <h4>${contract.serviceName}</h4>
              <p>商户：${contract.merchantName}</p>
            </div>
            <span class="${meta.className}">${meta.label}</span>
          </header>
          <dl class="contract-card__meta">
            <div>
              <dt>服务地区</dt>
              <dd>${regions}</dd>
            </div>
            <div>
              <dt>服务期限</dt>
              <dd>${formatDateRange(contract.startDate, contract.endDate)}</dd>
            </div>
            <div>
              <dt>产品/项目</dt>
              <dd>${products}</dd>
            </div>
            <div>
              <dt>负责人</dt>
              <dd>${contract.contactName} · ${contract.contactPhone}</dd>
            </div>
          </dl>
          ${suspensionNotice}
          <footer class="contract-card__actions">
            ${actions.join("")}
          </footer>
        </article>
      `;
    })
    .join("");
}

function formatDateRange(start, end) {
  if (!start && !end) return "未设置";
  if (!start) return `截至 ${end}`;
  if (!end) return `自 ${start} 起`;
  return `${start} 至 ${end}`;
}

function getContractBucket(status) {
  if (status === "pending") return "pending";
  if (status === "active") return "active";
  if (status === "suspended") return "suspended";
  // cancelled, rejected, expired 都归入 terminated 分类
  return "terminated";
}

function getLatestSuspension(contract) {
  const history = contract?.suspensionHistory || [];
  if (!history.length) return null;
  return history[history.length - 1];
}

function getLatestTermination(contract) {
  const history = contract?.terminationHistory || [];
  if (!history.length) return null;
  return history[history.length - 1];
}

function renderSuspensionInfo(contract) {
  const latest = getLatestSuspension(contract);
  if (!latest) return "";
  const label = contract.status === "paused" ? "当前暂停原因" : "最近暂停记录";
  return `
    <div class="contracts-detail__alert contracts-detail__alert--paused">
      <span class="contracts-detail__label">${label}</span>
      <p>${escapeHtml(latest.reason)} · ${escapeHtml(
    latest.time
  )} · ${escapeHtml(latest.actor)}</p>
    </div>
  `;
}

function renderTerminationInfo(contract) {
  const latest = getLatestTermination(contract);
  if (!latest) return "";
  return `
    <div class="contracts-detail__alert contracts-detail__alert--terminated">
      <span class="contracts-detail__label">终止说明</span>
      <p>${escapeHtml(latest.reason)} · ${escapeHtml(
    latest.time
  )} · ${escapeHtml(latest.actor)}</p>
    </div>
  `;
}

function renderReadonlyField(label, value) {
  const displayValue = value ? escapeHtml(value) : "—";
  return `
    <div class="form-field">
      <label>${label}</label>
      <input type="text" value="${displayValue}" readonly />
    </div>
  `;
}

function renderReadonlyTextarea(label, value) {
  const displayValue = value ? escapeHtml(value) : "—";
  return `
    <div class="form-field">
      <label>${label}</label>
      <textarea rows="3" readonly>${displayValue}</textarea>
    </div>
  `;
}

function buildContractDetailModal(contract) {
  const meta = CONTRACT_STATUS_META[contract.status];
  const serviceItems = contract.serviceItems?.length
    ? contract.serviceItems.join("、")
    : (contract.products || []).join("、");
  const infoFields = [
    renderReadonlyField("合同编号", contract.code),
    renderReadonlyField("服务名称", contract.serviceName),
    renderReadonlyField("商户名称", contract.merchantName),
    renderReadonlyField("服务商名称", contract.providerName),
    renderReadonlyField("服务地区", contract.regions.join("、")),
    renderReadonlyField(
      "服务期限",
      formatDateRange(contract.startDate, contract.endDate)
    ),
    renderReadonlyField(
      "联系人",
      `${contract.contactName} · ${contract.contactPhone}`
    ),
    renderReadonlyField("服务项目", serviceItems),
  ].join("");

  const clausesHtml = (contract.clauses || [])
    .map(
      (clause) =>
        `<li><strong>${escapeHtml(clause.title)}</strong><p>${escapeHtml(
          clause.content
        )}</p></li>`
    )
    .join("");

  const attachmentsHtml = (contract.attachments || [])
    .map(
      (file) =>
        `<li><span>${escapeHtml(
          file.name
        )}</span><button class="btn btn--ghost" data-action="contract-download" data-contract="${
          contract.id
        }">下载</button></li>`
    )
    .join("");

  const timelineHtml = (contract.timeline || [])
    .map(
      (event) => `
        <div class="timeline__item">
          <div style="color: var(--color-neutral-600); font-size: 12px;">${escapeHtml(
            event.time
          )}</div>
          <div style="margin:4px 0;">${escapeHtml(event.text)}</div>
          <div style="color: var(--color-neutral-500); font-size: 12px;">${escapeHtml(
            event.actor
          )}</div>
        </div>`
    )
    .join("");

  const rejectionHtml =
    contract.rejectionHistory && contract.rejectionHistory.length
      ? `<section class="contracts-detail__section">
          <h4>拒绝记录</h4>
          <ul class="contracts-detail__rejections">
            ${contract.rejectionHistory
              .map(
                (item) =>
                  `<li><span>${escapeHtml(item.time)}</span><p>${escapeHtml(
                    item.reason
                  )}</p><span class="contracts-detail__label">处理人：${escapeHtml(
                    item.actor
                  )}</span></li>`
              )
              .join("")}
          </ul>
        </section>`
      : "";

  const clausesSection = clausesHtml || "<li>暂无条款记录</li>";
  const attachmentsSection = attachmentsHtml || "<li>暂无附件</li>";
  const timelineSection =
    timelineHtml ||
    `<div class="timeline__item">
      <div style="color: var(--color-neutral-600); font-size: 12px;">—</div>
      <div style="margin:4px 0;">暂无时间线记录</div>
    </div>`;

  return `
    <div class="contracts-detail__content contracts-detail__content--modal">
      <header class="contracts-detail__header">
        <div>
          <h3>${escapeHtml(contract.serviceName)}</h3>
          <p>合同编号：${escapeHtml(contract.code)} · 商户：${escapeHtml(
    contract.merchantName
  )}</p>
          <p class="contract-modal__meta">最近更新：${escapeHtml(
            contract.lastUpdatedAt || "—"
          )}</p>
        </div>
        <span class="${meta.className}">${meta.label}</span>
      </header>
      ${renderSuspensionInfo(contract)}
      ${renderTerminationInfo(contract)}
      <section class="contracts-detail__section">
        <h4>基本信息</h4>
        <div class="form-grid contract-modal__grid">
          ${infoFields}
          ${renderReadonlyTextarea("服务内容", contract.serviceContent)}
          ${renderReadonlyTextarea("付款方式", contract.paymentTerms)}
          ${renderReadonlyTextarea("违约责任", contract.breachLiability)}
        </div>
      </section>
      <section class="contracts-detail__section">
        <h4>合同条款</h4>
        <ul class="contracts-detail__clauses">
          ${clausesSection}
        </ul>
      </section>
      <section class="contracts-detail__section">
        <h4>附件</h4>
        <ul class="contracts-detail__attachments">
          ${attachmentsSection}
        </ul>
      </section>
      <section class="contracts-detail__section">
        <h4>时间线</h4>
        <div class="timeline">
          ${timelineSection}
        </div>
      </section>
      ${rejectionHtml}
    </div>
  `;
}

function setContractView(view) {
  state.contractView = view;
  state.selectedContractId = null;
  renderContracts();
}

function openContractDetail(contractId) {
  const contract = state.contracts.find((item) => item.id === contractId);
  if (!contract) {
    showToast("未找到合同信息", "error");
    return;
  }
  state.selectedContractId = contractId;
  const filtered = getFilteredContracts();
  renderContractList(filtered);

  const body = buildContractDetailModal(contract);
  openModal({
    title: "合同详情",
    body,
    confirmText: "关闭",
    cancelText: "返回列表",
    onConfirm: () => {
      closeModal();
      return false;
    },
  });
  const modalContent =
    els.modal.querySelector && els.modal.querySelector(".modal__content");
  if (modalContent) {
    modalContent.classList.add("modal__content--wide");
  }
}

function handleContractSearchSubmit(event) {
  if (event) event.preventDefault();
  if (!els.contractFilterForm) return;
  const formData = new FormData(els.contractFilterForm);
  state.contractFilters = {
    provider: formData.get("provider") || state.contractFilters.provider || "",
    serviceName: (formData.get("serviceName") || "").trim(),
    regions: formData.getAll("regions"),
    startDate: formData.get("startDate") || "",
    endDate: formData.get("endDate") || "",
  };
  renderContracts();
}

function handleContractReset() {
  state.contractFilters = {
    provider: "盛唐维修服务有限公司",
    serviceName: "",
    regions: [],
    startDate: "",
    endDate: "",
  };
  if (els.contractFilterForm) {
    els.contractFilterForm.reset();
  }
  renderContracts();
}

function confirmContract(contractId) {
  const contract = state.contracts.find((item) => item.id === contractId);
  if (!contract) return;
  openModal({
    title: `确认合同：${contract.serviceName}`,
    body: `
      <p>确认后合同将立即生效，并通知商户「${contract.merchantName}」。</p>
      <p style="margin-top:8px; color: var(--color-neutral-600);">请确认已完成条款核对及内部审批。</p>
    `,
    confirmText: "确认生效",
    onConfirm: () => {
      contract.status = "active";
      const now = getCurrentTimeText();
      contract.timeline.push({
        time: now,
        actor: "盛唐维修",
        text: "服务商确认合同，合同已生效。",
      });
      contract.lastUpdatedAt = now;
      state.contractView = "active";
      state.selectedContractId = contractId;
      showToast(`合同 ${contract.code} 已确认生效`, "success");
      renderContracts();
    },
  });
}

function rejectContract(contractId) {
  const contract = state.contracts.find((item) => item.id === contractId);
  if (!contract) return;
  openModal({
    title: `拒绝合同：${contract.serviceName}`,
    body: `
      <p>请填写拒绝原因，将同步通知商户。</p>
      <textarea id="contract-reject-reason" rows="4" style="width:100%; padding:12px; border-radius:6px; border:1px solid var(--color-neutral-200);" placeholder="请输入拒绝原因"></textarea>
    `,
    confirmText: "提交拒绝",
    onConfirm: () => {
      const reasonInput = document.getElementById("contract-reject-reason");
      const reason = reasonInput ? reasonInput.value.trim() : "";
      if (!reason) {
        showToast("请填写拒绝原因", "error");
        return false;
      }
      contract.status = "rejected";
      const now = getCurrentTimeText();
      contract.timeline.push({
        time: now,
        actor: "盛唐维修",
        text: `服务商拒绝合同，原因：${reason}`,
      });
      contract.rejectionHistory.push({
        time: now,
        actor: "盛唐维修",
        reason,
      });
      contract.lastUpdatedAt = now;
      state.contractView = "terminated";
      state.selectedContractId = contractId;
      showToast(`已拒绝合同 ${contract.code}，原因已记录`, "info");
      renderContracts();
    },
  });
}

function suspendContract(contractId) {
  const contract = state.contracts.find((item) => item.id === contractId);
  if (!contract) return;
  if (contract.status !== "active") {
    showToast("仅生效中的合同可以发起暂停申请", "warning");
    return;
  }
  openModal({
    title: `暂停合同：${contract.serviceName}`,
    body: `
      <p>请输入暂停原因，将反馈给平台与商户。</p>
      <textarea id="contract-suspend-reason" rows="4" style="width:100%; padding:12px; border-radius:6px; border:1px solid var(--color-neutral-200);" placeholder="例如：商户结算调整，需要暂停履约"></textarea>
    `,
    confirmText: "提交暂停申请",
    onConfirm: () => {
      const textarea = document.getElementById("contract-suspend-reason");
      const reason = textarea ? textarea.value.trim() : "";
      if (!reason) {
        showToast("请填写暂停原因", "error");
        return false;
      }
      const now = getCurrentTimeText();
      contract.status = "suspended";
      contract.suspensionHistory = contract.suspensionHistory || [];
      contract.suspensionHistory.push({
        time: now,
        actor: "盛唐维修",
        reason,
      });
      contract.timeline.push({
        time: now,
        actor: "盛唐维修",
        text: `提交暂停申请，原因：${reason}`,
      });
      contract.lastUpdatedAt = now;
      state.contractView = "suspended";
      state.selectedContractId = contractId;
      showToast(`合同 ${contract.code} 已提交暂停申请`, "info");
      renderContracts();
    },
  });
}

function restoreContract(contractId) {
  const contract = state.contracts.find((item) => item.id === contractId);
  if (!contract) return;
  if (contract.status !== "suspended") {
    showToast("仅暂停中的合同可以恢复", "warning");
    return;
  }
  openModal({
    title: `恢复合同：${contract.serviceName}`,
    body: `
      <p>确认恢复合同后，后续服务单将重新派发给本服务商。</p>
    `,
    confirmText: "确认恢复",
    onConfirm: () => {
      const now = getCurrentTimeText();
      contract.status = "active";
      contract.timeline.push({
        time: now,
        actor: "盛唐维修",
        text: "恢复合同，继续履约。",
      });
      contract.lastUpdatedAt = now;
      state.contractView = "active";
      state.selectedContractId = contractId;
      showToast(`合同 ${contract.code} 已恢复生效`, "success");
      renderContracts();
    },
  });
}

function cancelContract(contractId) {
  const contract = state.contracts.find((item) => item.id === contractId);
  if (!contract) return;
  if (contract.status !== "active" && contract.status !== "suspended") {
    showToast("仅生效或暂停状态的合同可以取消", "warning");
    return;
  }
  openModal({
    title: `取消合同：${contract.serviceName}`,
    body: `
      <p>请输入取消原因，平台将同步给商户。</p>
      <textarea id="contract-cancel-reason" rows="4" style="width:100%; padding:12px; border-radius:6px; border:1px solid var(--color-neutral-200);" placeholder="例如：商户终止合作，需取消合同"></textarea>
    `,
    confirmText: "提交取消",
    onConfirm: () => {
      const textarea = document.getElementById("contract-cancel-reason");
      const reason = textarea ? textarea.value.trim() : "";
      if (!reason) {
        showToast("请填写取消原因", "error");
        return false;
      }
      const now = getCurrentTimeText();
      contract.status = "cancelled";
      contract.terminationHistory = contract.terminationHistory || [];
      contract.terminationHistory.push({
        time: now,
        actor: "盛唐维修",
        reason,
      });
      contract.timeline.push({
        time: now,
        actor: "盛唐维修",
        text: `提交取消申请，原因：${reason}`,
      });
      contract.lastUpdatedAt = now;
      state.contractView = "terminated";
      state.selectedContractId = contractId;
      showToast(`合同 ${contract.code} 已取消`, "info");
      renderContracts();
    },
  });
}

function downloadContract(contractId) {
  const contract = state.contracts.find((item) => item.id === contractId);
  if (!contract) return;
  showToast(`合同 ${contract.code} 的下载链接已发送至企业邮箱`, "info");
}

function getCurrentTimeText() {
  const now = new Date();
  const yyyy = now.getFullYear();
  const mm = String(now.getMonth() + 1).padStart(2, "0");
  const dd = String(now.getDate()).padStart(2, "0");
  const hh = String(now.getHours()).padStart(2, "0");
  const mi = String(now.getMinutes()).padStart(2, "0");
  return `${yyyy}-${mm}-${dd} ${hh}:${mi}`;
}

function renderTeam() {
  // 应用搜索和筛选条件
  const filtered = state.team.filter((member) => {
    // 搜索条件：姓名、联系方式、角色
    const searchMatch = state.teamSearch
      ? [member.name, member.contact, member.role].some((field) =>
          field.toLowerCase().includes(state.teamSearch.toLowerCase())
        )
      : true;

    // 状态筛选
    const statusMatch =
      state.teamStatusFilter === "all" ||
      member.status === state.teamStatusFilter;

    // 角色筛选
    const roleMatch =
      state.teamRoleFilter === "all" || member.role === state.teamRoleFilter;

    return searchMatch && statusMatch && roleMatch;
  });

  // 如果没有符合条件的员工，显示空状态
  if (!filtered.length) {
    els.teamTableBody.innerHTML = "";
    els.teamEmpty.classList.remove("hidden");
    return;
  }

  els.teamEmpty.classList.add("hidden");

  els.teamTableBody.innerHTML = filtered
    .map((member) => {
      const statusTag =
        member.status === "active" ? "tag tag--success" : "tag tag--warning";
      const statusLabel = member.status === "active" ? "正常" : "已暂停";
      const actions = [];
      if (member.status === "active") {
        actions.push({
          label: "暂停",
          action: "team-pause",
          style: "btn--ghost",
        });
      } else {
        actions.push({
          label: "恢复",
          action: "team-resume",
          style: "btn--primary",
        });
      }
      actions.push({
        label: "删除",
        action: "team-delete",
        style: "btn--ghost",
      });
      return `
        <tr>
          <td>${member.name}</td>
          <td>${member.contact}</td>
          <td>${member.role}</td>
          <td><span class="${statusTag}">${statusLabel}</span></td>
          <td class="table-actions">${actions
            .map(
              (act) =>
                `<button class="btn ${act.style}" data-action="${act.action}" data-member="${member.id}">${act.label}</button>`
            )
            .join("")}</td>
        </tr>`;
    })
    .join("");
}

function renderAccount() {
  els.accountAlert.textContent = state.account.pendingMessage || "";
  els.accountAlert.classList.toggle("hidden", !state.account.pendingMessage);

  els.accountTabs.innerHTML = `
    <div class="tab active" data-tab-target="company">公司资料</div>
    <div class="tab" data-tab-target="region">服务区域</div>
    <div class="tab" data-tab-target="qualification">资质文件</div>`;

  els.accountCompany.innerHTML = `
    <div class="card card--wide">
      <div class="card__label">基本信息</div>
      <div class="chip-row">
        <span class="chip">账户 ID：${state.account.company.id}</span>
        <span class="chip">服务类型：${state.account.company.category}</span>
        <span class="chip">联系人：${state.account.company.contact}</span>
      </div>
      <div style="margin: 16px 0;">
        <div><strong>账户名称：</strong>${state.account.company.name}</div>
        <div><strong>服务商品类型：</strong>${state.account.company.serviceProducts}</div>
        <div><strong>服务地址：</strong>${state.account.company.address}</div>
        <div><strong>联系方式：</strong>${state.account.company.contact}</div>
        <div><strong>服务时间：</strong>${state.account.company.serviceHours}</div>
        <div><strong>营业执照：</strong>${state.account.company.businessLicense}</div>
      </div>
      <div class="table-actions">
        <button class="btn btn--primary" data-action="account-edit">申请变更信息</button>
      </div>
    </div>`;

  els.accountRegions.innerHTML = `
    <div class="card card--wide">
      <div class="card__label">当前服务地区</div>
      <div style="margin: 16px 0;">
        ${state.account.regions
          .map((region) => {
            let tagClass, tagLabel;
            if (region.status === "active") {
              tagClass = "tag tag--success";
              tagLabel = "生效中";
            } else if (region.status === "pending") {
              tagClass = "tag tag--warning";
              tagLabel = "待审核";
            } else if (region.status === "removing") {
              tagClass = "tag tag--danger";
              tagLabel = "待移除";
            } else {
              tagClass = "tag tag--info";
              tagLabel = "未知状态";
            }
            return `
            <div style="display: flex; justify-content: space-between; align-items: center; padding: 12px; border: 1px solid var(--color-neutral-200); border-radius: 6px; margin-bottom: 8px;">
              <div>
                <strong>${region.name}</strong>
                <span class="${tagClass}" style="margin-left: 12px;">${tagLabel}</span>
              </div>
            </div>
          `;
          })
          .join("")}
      </div>
      <div class="table-actions">
        <button class="btn btn--primary" data-action="account-change-regions">申请变更服务地区</button>
      </div>
    </div>
  `;

  els.accountFiles.innerHTML = state.account.files
    .map((file) => {
      const tagClass =
        file.status === "approved" ? "tag tag--success" : "tag tag--warning";
      const tagLabel = file.status === "approved" ? "已通过" : "待审核";
      return `
        <div class="list-item">
          <span>${file.name}</span>
          <div class="table-actions">
            <span class="${tagClass}">${tagLabel}</span>
            <button class="btn btn--ghost" data-action="account-preview-file" data-file="${file.name}">预览</button>
            <button class="btn btn--ghost" data-action="account-update-file" data-file="${file.name}">更新</button>
          </div>
        </div>`;
    })
    .join("");

  bindAccountTabs();
}

function renderNotifications() {
  els.notificationsList.innerHTML = state.notifications
    .map((notice) => {
      const tagClass =
        notice.type === "danger"
          ? "tag tag--danger"
          : notice.type === "success"
          ? "tag tag--success"
          : "tag tag--info";
      return `
        <div class="list-item" data-notice="${notice.id}">
          <span>${notice.text}</span>
          <div class="table-actions">
            <span class="${tagClass}">${notice.read ? "已读" : "未读"}</span>
            <button class="btn btn--ghost" data-action="notification-open" data-notice="${
              notice.id
            }">查看</button>
            ${
              notice.read
                ? ""
                : `<button class="btn btn--ghost" data-action="notification-read" data-notice="${notice.id}">标记已读</button>`
            }
          </div>
        </div>`;
    })
    .join("");
}

function showToast(message, type = "info") {
  const toast = document.createElement("div");
  toast.className = `toast toast--${type}`;
  toast.innerHTML = `<span>${message}</span><button class="btn btn--ghost">关闭</button>`;
  toast.querySelector("button").addEventListener("click", () => toast.remove());
  els.toastContainer.appendChild(toast);
  setTimeout(() => {
    toast.classList.add("hidden");
    setTimeout(() => toast.remove(), 200);
  }, TOAST_DURATION);
}

function openModal({
  title,
  body,
  confirmText = "确认",
  cancelText = "取消",
  onConfirm,
}) {
  els.modalTitle.textContent = title;
  els.modalBody.innerHTML = body;
  els.modalConfirm.textContent = confirmText;
  els.modalCancel.textContent = cancelText;
  modalConfirmHandler = onConfirm || null;
  els.modal.classList.add("active");
}

function closeModal() {
  els.modal.classList.remove("active");
  const modalContent =
    els.modal.querySelector && els.modal.querySelector(".modal__content");
  if (modalContent) {
    modalContent.classList.remove("modal__content--wide");
  }
  els.modalBody.innerHTML = "";
  if (els.modalCancel) {
    els.modalCancel.textContent = "取消";
  }
  modalConfirmHandler = null;
}

function translateBilling(billing) {
  switch (billing) {
    case "per_order":
      return "次";
    case "per_hour":
      return "小时";
    case "per_unit":
      return "件";
    default:
      return "次";
  }
}

function escapeHtml(value) {
  return String(value ?? "")
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;")
    .replace(/"/g, "&quot;")
    .replace(/'/g, "&#39;");
}

function handleOrderDetail(orderId) {
  const order = state.orders.find((item) => item.id === orderId);
  if (!order) return;

  const meta = ORDER_STATUS_META[order.status];
  const statusText = `服务单状态：${meta.label} · ${
    order.expectedFinish ? `预计完成 ${order.expectedFinish}` : "无预计时间"
  }`;

  // 构建关联信息HTML（用例032要求）
  const relatedInfoHtml = `
    <div style="background: var(--color-info-100); padding: 12px; border-radius: 6px; margin-bottom: 16px;">
      <h4 style="margin: 0 0 8px 0; color: var(--color-info-700);">关联信息</h4>
      <div style="display: flex; flex-wrap: wrap; gap: 8px;">
        ${order.aftersaleId ? `<span style="background: var(--color-info-200); color: var(--color-info-800); padding: 4px 8px; border-radius: 4px; font-size: 12px; cursor: pointer;" onclick="alert('跳转到售后单 ${order.aftersaleId}')">📋 售后单：${order.aftersaleId}</span>` : ''}
        ${order.orderId ? `<span style="background: var(--color-info-200); color: var(--color-info-800); padding: 4px 8px; border-radius: 4px; font-size: 12px; cursor: pointer;" onclick="alert('跳转到订单 ${order.orderId}')">🛒 订单：${order.orderId}</span>` : ''}
        ${order.waybillNumber ? `<span style="background: var(--color-info-200); color: var(--color-info-800); padding: 4px 8px; border-radius: 4px; font-size: 12px;">📦 快递单号：${order.waybillNumber}</span>` : ''}
      </div>
    </div>`;

  openModal({
    title: `服务单详情：${order.id}`,
    body: `
      <div style="margin-bottom: 16px;">
        <div style="background: var(--color-neutral-100); padding: 12px; border-radius: 6px; margin-bottom: 16px;">
          <strong>${statusText}</strong>
        </div>
        
        ${relatedInfoHtml}
        
        <div style="display: grid; grid-template-columns: repeat(2, 1fr); gap: 16px; margin-bottom: 16px;">
          <div>
            <h4 style="margin: 0 0 8px 0; color: var(--color-neutral-700);">关键信息</h4>
            <div style="display: flex; flex-wrap: wrap; gap: 8px;">
              <span style="background: var(--color-primary-100); color: var(--color-primary-700); padding: 4px 8px; border-radius: 4px; font-size: 12px;">服务单号：${
                order.id
              }</span>
              <span style="background: var(--color-primary-100); color: var(--color-primary-700); padding: 4px 8px; border-radius: 4px; font-size: 12px;">商户：${
                order.merchant
              }</span>
              <span style="background: var(--color-primary-100); color: var(--color-primary-700); padding: 4px 8px; border-radius: 4px; font-size: 12px;">服务类型：${
                order.serviceType
              }</span>
              <span style="background: var(--color-primary-100); color: var(--color-primary-700); padding: 4px 8px; border-radius: 4px; font-size: 12px;">优先级：${
                order.priority
              }</span>
            </div>
          </div>
          
          <div>
            <h4 style="margin: 0 0 8px 0; color: var(--color-neutral-700);">客户信息</h4>
            <div style="font-size: 14px; line-height: 1.5;">
              <div><strong>${order.customer.name}</strong> · ${
      order.customer.phone
    }</div>
              <div style="color: var(--color-neutral-600);">${
                order.customer.address
              }</div>
            </div>
          </div>
        </div>
        
        <div style="display: grid; grid-template-columns: repeat(2, 1fr); gap: 16px; margin-bottom: 16px;">
          <div>
            <h4 style="margin: 0 0 8px 0; color: var(--color-neutral-700);">商品与故障</h4>
            <div style="font-size: 14px; line-height: 1.5;">
              <div><strong>${order.product}</strong></div>
              <div style="color: var(--color-neutral-600);">${order.notes}</div>
            </div>
          </div>
          
          <div>
            <h4 style="margin: 0 0 8px 0; color: var(--color-neutral-700);">派工信息</h4>
            <div style="font-size: 14px; line-height: 1.5;">
              <div>已指派：<strong>${
                order.assignedTo || "未指派"
              }</strong></div>
              <div>${order.received ? "已确认收件" : "尚未收件"}</div>
            </div>
          </div>
        </div>
        
        <div>
          <h4 style="margin: 0 0 8px 0; color: var(--color-neutral-700);">状态时间轴</h4>
          <div style="border-left: 2px solid var(--color-neutral-200); padding-left: 16px;">
            ${order.timeline
              .map(
                (event) => `
              <div style="margin-bottom: 12px; position: relative;">
                <div style="position: absolute; left: -20px; top: 4px; width: 8px; height: 8px; background: var(--color-primary-500); border-radius: 50%;"></div>
                <div style="font-size: 14px; line-height: 1.4;">
                  <div style="color: var(--color-neutral-600); font-size: 12px;">${event.time}</div>
                  <div style="margin: 4px 0;">${event.text}</div>
                  <div style="color: var(--color-neutral-500); font-size: 12px;">${event.actor}</div>
                </div>
              </div>
            `
              )
              .join("")}
          </div>
        </div>
      </div>
    `,
    confirmText: "关闭",
    onConfirm: () => {
      closeModal();
    },
  });
}

// 接受服务单（状态：pending_confirm → received）
function handleOrderAccept(orderId) {
  const order = state.orders.find((item) => item.id === orderId);
  if (!order) return;
  openModal({
    title: `接受服务单：${order.id}`,
    body: `
      <p>确认接受此服务单？接受后需要进行派工。</p>
      <div style="background: var(--color-neutral-100); padding: 12px; border-radius: 6px; margin-top: 12px;">
        <div><strong>商户：</strong>${order.merchant}</div>
        <div><strong>服务类型：</strong>${order.serviceType}</div>
        <div><strong>客户：</strong>${order.customer.name} · ${order.customer.phone}</div>
        <div><strong>地址：</strong>${order.customer.address}</div>
      </div>
    `,
    confirmText: "确认接受",
    onConfirm: () => {
      order.status = "received";
      order.timeline.push({
        time: getCurrentTimeText(),
        text: "服务商接受服务单",
        actor: "王主管",
      });
      state.ordersFilter = "received";
      showToast(`已接受服务单 ${order.id}，请尽快派工`, "success");
      closeModal();
      renderOrders();
      renderDashboard();
    },
  });
}

// 拒绝服务单（状态：pending_confirm → cancelled）
function handleOrderReject(orderId) {
  const order = state.orders.find((item) => item.id === orderId);
  if (!order) return;
  openModal({
    title: `拒绝服务单：${order.id}`,
    body: `
      <p>请输入拒绝原因，将通知商户重新派单：</p>
      <textarea id="reject-reason" rows="3" style="width:100%; padding:12px; border-radius:6px; border:1px solid var(--color-neutral-200);" placeholder="例如：超出服务范围、人手不足等"></textarea>
    `,
    confirmText: "确认拒绝",
    onConfirm: () => {
      const reason = document.getElementById("reject-reason").value.trim();
      if (!reason) {
        showToast("请填写拒绝原因", "error");
        return false;
      }
      order.status = "cancelled";
      order.timeline.push({
        time: getCurrentTimeText(),
        text: `服务商拒绝服务单，原因：${reason}`,
        actor: "王主管",
      });
      showToast(`已拒绝服务单 ${order.id}，已通知商户`, "info");
      closeModal();
      renderOrders();
      renderDashboard();
    },
  });
}

// 派工（状态：received → assigned）- 用例033
function handleOrderAssign(orderId) {
  const order = state.orders.find((item) => item.id === orderId);
  if (!order) return;
  const technicians = state.team.filter(
    (member) => member.role === "维修师傅" && member.status === "active"
  );
  if (!technicians.length) {
    showToast("暂无可用维修师傅，请先在团队管理中添加", "error");
    return;
  }
  // 显示维修师傅列表（用例033要求）
  const techListHtml = technicians
    .map(
      (tech) => `
    <label style="display: flex; align-items: center; padding: 12px; border: 1px solid var(--color-neutral-200); border-radius: 6px; margin-bottom: 8px; cursor: pointer;">
      <input type="radio" name="technician" value="${tech.name}" style="margin-right: 12px;" />
      <div style="flex: 1;">
        <div><strong>${tech.name}</strong></div>
        <div style="font-size: 12px; color: var(--color-neutral-600);">联系方式：${tech.contact}</div>
      </div>
      <span class="tag tag--success">可用</span>
    </label>
  `
    )
    .join("");

  openModal({
    title: `派工：${order.id}`,
    body: `
      <p style="margin-bottom: 12px;">选择维修师傅：</p>
      <div style="max-height: 300px; overflow-y: auto;">
        ${techListHtml}
      </div>
      <textarea id="assign-note" rows="2" style="width:100%; margin-top:12px; padding:12px; border-radius:6px; border:1px solid var(--color-neutral-200);" placeholder="派工备注（可选）"></textarea>
    `,
    confirmText: "确认派工",
    onConfirm: () => {
      const selected = document.querySelector(
        'input[name="technician"]:checked'
      );
      if (!selected) {
        showToast("请选择维修师傅", "error");
        return false;
      }
      const technician = selected.value;
      order.status = "assigned";
      order.assignedTo = technician;
      order.timeline.push({
        time: getCurrentTimeText(),
        text: `指派维修师傅：${technician}`,
        actor: "王主管",
      });
      state.ordersFilter = "assigned";
      showToast(`已派工给 ${technician}`, "success");
      closeModal();
      renderOrders();
      renderDashboard();
    },
  });
}

// 重新派工（状态：assigned → assigned，更换维修师傅）
function handleOrderReassign(orderId) {
  const order = state.orders.find((item) => item.id === orderId);
  if (!order) return;
  const technicians = state.team.filter(
    (member) =>
      member.role === "维修师傅" &&
      member.status === "active" &&
      member.name !== order.assignedTo
  );
  if (!technicians.length) {
    showToast("暂无其他可用维修师傅", "error");
    return;
  }
  const techListHtml = technicians
    .map(
      (tech) => `
    <label style="display: flex; align-items: center; padding: 12px; border: 1px solid var(--color-neutral-200); border-radius: 6px; margin-bottom: 8px; cursor: pointer;">
      <input type="radio" name="technician" value="${tech.name}" style="margin-right: 12px;" />
      <div style="flex: 1;">
        <div><strong>${tech.name}</strong></div>
        <div style="font-size: 12px; color: var(--color-neutral-600);">联系方式：${tech.contact}</div>
      </div>
    </label>
  `
    )
    .join("");

  openModal({
    title: `重新派工：${order.id}`,
    body: `
      <p>当前指派：<strong>${order.assignedTo}</strong></p>
      <p style="margin: 12px 0;">选择新的维修师傅：</p>
      <div style="max-height: 250px; overflow-y: auto;">
        ${techListHtml}
      </div>
      <textarea id="reassign-reason" rows="2" style="width:100%; margin-top:12px; padding:12px; border-radius:6px; border:1px solid var(--color-neutral-200);" placeholder="重新派工原因"></textarea>
    `,
    confirmText: "确认重新派工",
    onConfirm: () => {
      const selected = document.querySelector(
        'input[name="technician"]:checked'
      );
      const reason = document.getElementById("reassign-reason").value.trim();
      if (!selected) {
        showToast("请选择维修师傅", "error");
        return false;
      }
      const oldTech = order.assignedTo;
      const newTech = selected.value;
      order.assignedTo = newTech;
      order.timeline.push({
        time: getCurrentTimeText(),
        text: `重新派工：${oldTech} → ${newTech}${
          reason ? `，原因：${reason}` : ""
        }`,
        actor: "王主管",
      });
      showToast(`已重新派工给 ${newTech}`, "success");
      closeModal();
      renderOrders();
    },
  });
}

// 上门签到（状态：assigned → on_site）
function handleOrderOnsite(orderId) {
  const order = state.orders.find((item) => item.id === orderId);
  if (!order) return;
  openModal({
    title: `上门签到：${order.id}`,
    body: `
      <p>确认维修师傅 <strong>${order.assignedTo}</strong> 已到达客户现场？</p>
      <div style="background: var(--color-neutral-100); padding: 12px; border-radius: 6px; margin-top: 12px;">
        <div><strong>客户：</strong>${order.customer.name}</div>
        <div><strong>地址：</strong>${order.customer.address}</div>
      </div>
    `,
    confirmText: "确认签到",
    onConfirm: () => {
      order.status = "on_site";
      order.timeline.push({
        time: getCurrentTimeText(),
        text: "维修师傅上门签到",
        actor: order.assignedTo,
      });
      state.ordersFilter = "on_site";
      showToast(`${order.assignedTo} 已上门签到`, "success");
      closeModal();
      renderOrders();
      renderDashboard();
    },
  });
}

// 退回服务单（状态：assigned/item_received/on_site → returned）
function handleOrderReturn(orderId) {
  const order = state.orders.find((item) => item.id === orderId);
  if (!order) return;
  openModal({
    title: `退回服务单：${order.id}`,
    body: `
      <p>请输入退回原因：</p>
      <textarea id="return-reason" rows="3" style="width:100%; padding:12px; border-radius:6px; border:1px solid var(--color-neutral-200);" placeholder="例如：商品不符合维修条件、超出服务范围等"></textarea>
    `,
    confirmText: "确认退回",
    onConfirm: () => {
      const reason = document.getElementById("return-reason").value.trim();
      if (!reason) {
        showToast("请填写退回原因", "error");
        return false;
      }
      order.status = "returned";
      order.timeline.push({
        time: getCurrentTimeText(),
        text: `维修师傅退回服务单，原因：${reason}`,
        actor: order.assignedTo || "王主管",
      });
      state.ordersFilter = "returned";
      showToast(`服务单 ${order.id} 已退回`, "info");
      closeModal();
      renderOrders();
      renderDashboard();
    },
  });
}

// 确认收件（状态：assigned → item_received）- 用例035
function handleOrderReceive(orderId) {
  const order = state.orders.find((item) => item.id === orderId);
  if (!order) return;
  if (!order.requireReceipt) {
    showToast("该服务单无需收件确认", "info");
    return;
  }
  openModal({
    title: `确认收件：${order.id}`,
    body: `
      <p>请确认已收到顾客寄出的商品：</p>
      <div class="form-field" style="margin-top: 12px;">
        <label>快递单号 *</label>
        <input id="receive-waybill" type="text" style="width:100%; padding:12px; border-radius:6px; border:1px solid var(--color-neutral-200);" placeholder="输入快递单号" value="${
          order.waybillNumber || ""
        }" />
      </div>
      <div class="form-field" style="margin-top: 12px;">
        <label>收件备注</label>
        <textarea id="receive-note" rows="3" style="width:100%; padding:12px; border-radius:6px; border:1px solid var(--color-neutral-200);" placeholder="收件备注（如包装完好、缺件说明等）"></textarea>
      </div>
      <div style="margin-top: 12px; padding: 12px; background: var(--color-info-100); border-radius: 6px;">
        <strong>商品信息：</strong>${order.product}<br/>
        <strong>故障描述：</strong>${order.notes}
      </div>
    `,
    confirmText: "确认收件",
    onConfirm: () => {
      const waybill = document.getElementById("receive-waybill").value.trim();
      if (!waybill) {
        showToast("请输入快递单号", "error");
        return false;
      }
      order.status = "item_received";
      order.received = true;
      order.waybillNumber = waybill;
      order.timeline.push({
        time: getCurrentTimeText(),
        text: `确认收件，快递单号 ${waybill}`,
        actor: order.assignedTo || "系统",
      });
      state.ordersFilter = "item_received";
      showToast(`已确认收件，服务单 ${order.id} 进入维修流程`, "success");
      closeModal();
      renderOrders();
      renderDashboard();
    },
  });
}

// 完成服务单（状态：item_received/on_site → completed）- 用例034
function handleOrderComplete(orderId) {
  const order = state.orders.find((item) => item.id === orderId);
  if (!order) return;
  openModal({
    title: `完成服务单：${order.id}`,
    body: `
      <p>确认已完成客户服务？</p>
      <div class="form-field" style="margin-top: 12px;">
        <label>服务结果 *</label>
        <textarea id="complete-note" rows="3" style="width:100%; padding:12px; border-radius:6px; border:1px solid var(--color-neutral-200);" placeholder="填写服务结果、使用材料、维修情况等"></textarea>
      </div>
      <div class="form-field" style="margin-top: 12px;">
        <label>上传照片（可选）</label>
        <input type="file" accept="image/*" style="width:100%; padding:12px; border-radius:6px; border:1px solid var(--color-neutral-200);" />
        <span style="font-size: 12px; color: var(--color-neutral-600);">上传维修完成后的照片作为凭证</span>
      </div>
    `,
    confirmText: "确认完成",
    onConfirm: () => {
      const note = document.getElementById("complete-note").value.trim();
      if (!note) {
        showToast("请填写服务结果", "error");
        return false;
      }
      order.status = "completed";
      order.timeline.push({
        time: getCurrentTimeText(),
        text: `服务完成：${note}`,
        actor: order.assignedTo || "系统",
      });
      state.ordersFilter = "completed";
      showToast(`服务单 ${order.id} 已完成`, "success");
      closeModal();
      renderOrders();
      renderDashboard();
    },
  });
}

function handleOrderCancel(orderId) {
  const order = state.orders.find((item) => item.id === orderId);
  if (!order) return;
  openModal({
    title: `取消服务单：${order.id}`,
    body: `
      <p>请输入取消原因：</p>
      <textarea id="cancel-reason" rows="3" style="width:100%; padding:12px; border-radius:6px; border:1px solid var(--color-neutral-200);" placeholder="例如：客户无法提供发票"></textarea>
    `,
    confirmText: "确认取消",
    onConfirm: () => {
      const reason = document.getElementById("cancel-reason").value.trim();
      if (!reason) {
        showToast("请填写取消原因", "error");
        return false;
      }
      order.status = "cancelled";
      order.timeline.push({
        time: new Date().toISOString().replace("T", " ").slice(0, 16),
        text: `服务单取消，原因：${reason}`,
        actor: "王主管",
      });
      showToast(`服务单 ${order.id} 已取消`, "info");
      closeModal();
      renderOrders();
      renderDashboard();
    },
  });
}

function bindAccountTabs() {
  const tabs = els.accountTabs.querySelectorAll(".tab");
  const panels = document.querySelectorAll("[data-tab-panel]");
  tabs.forEach((tab) => {
    tab.addEventListener("click", () => {
      const target = tab.dataset.tabTarget;
      tabs.forEach((item) =>
        item.classList.toggle("active", item.dataset.tabTarget === target)
      );
      panels.forEach((panel) => {
        panel.hidden = panel.dataset.tabPanel !== target;
      });
    });
  });
}

function handleAccountEdit() {
  // 检查是否有未完成的订单
  const pendingOrders = state.orders.filter(
    (order) => order.status === "available" || order.status === "in_progress"
  );

  if (pendingOrders.length > 0) {
    openModal({
      title: "无法申请变更",
      body: `
        <p>您当前有 ${
          pendingOrders.length
        } 个未完成的服务单，请先完成或撤销这些订单后再申请变更账户信息。</p>
        <div style="margin-top: 16px;">
          <strong>未完成的订单：</strong>
          <ul style="margin: 8px 0; padding-left: 20px;">
            ${pendingOrders
              .map((order) => `<li>${order.id} - ${order.merchant}</li>`)
              .join("")}
          </ul>
        </div>
      `,
      confirmText: "我知道了",
      onConfirm: () => {
        closeModal();
      },
    });
    return;
  }

  openModal({
    title: "申请变更账户信息",
    body: `
      <div style="display: grid; grid-template-columns: repeat(2, 1fr); gap: 16px;">
        <div class="form-field">
          <label>账户名称 *</label>
          <input id="account-name" type="text" placeholder="请输入账户名称" value="${state.account.company.name}" />
        </div>
        <div class="form-field">
          <label>服务商品类型 *</label>
          <input id="account-products" type="text" placeholder="例如：电视机、洗衣机、冰箱" value="${state.account.company.serviceProducts}" />
        </div>
        <div class="form-field">
          <label>服务地址 *</label>
          <input id="account-address" type="text" placeholder="请输入服务地址" value="${state.account.company.address}" />
        </div>
        <div class="form-field">
          <label>联系方式 *</label>
          <input id="account-contact" type="text" placeholder="请输入联系方式" value="${state.account.company.contact}" />
        </div>
        <div class="form-field">
          <label>服务时间 *</label>
          <input id="account-hours" type="text" placeholder="例如：周一至周日 08:00-21:00" value="${state.account.company.serviceHours}" />
        </div>
        <div class="form-field">
          <label>营业执照</label>
          <input id="account-license" type="text" placeholder="营业执照文件" value="${state.account.company.businessLicense}" />
        </div>
      </div>
      <div style="margin-top: 16px; padding: 12px; background: var(--color-warning-100); border-radius: 6px; border-left: 4px solid var(--color-warning-500);">
        <strong>注意事项：</strong>
        <ul style="margin: 8px 0; padding-left: 20px; font-size: 14px;">
          <li>变更申请提交后需要平台管理员审核</li>
          <li>审核期间账户信息保持不变</li>
          <li>审核结果将通过消息中心通知</li>
        </ul>
      </div>
    `,
    confirmText: "提交申请",
    onConfirm: () => {
      const name = document.getElementById("account-name").value.trim();
      const products = document.getElementById("account-products").value.trim();
      const address = document.getElementById("account-address").value.trim();
      const contact = document.getElementById("account-contact").value.trim();
      const hours = document.getElementById("account-hours").value.trim();
      const license = document.getElementById("account-license").value.trim();

      if (!name || !products || !address || !contact || !hours) {
        showToast("请填写所有必填信息", "error");
        return false;
      }

      // 检查是否有实际变更
      const hasChanges =
        name !== state.account.company.name ||
        products !== state.account.company.serviceProducts ||
        address !== state.account.company.address ||
        contact !== state.account.company.contact ||
        hours !== state.account.company.serviceHours ||
        license !== state.account.company.businessLicense;

      if (!hasChanges) {
        showToast("您没有进行任何修改", "warning");
        return false;
      }

      state.account.pendingMessage =
        "您的账户信息变更申请已提交，平台将在 24 小时内审核";
      showToast("变更申请已提交，请等待审核", "success");
      closeModal();
      renderAccount();
    },
  });
}

function handleAccountChangeRegions() {
  // 检查是否有未完成的订单
  const pendingOrders = state.orders.filter(
    (order) => order.status === "available" || order.status === "in_progress"
  );

  if (pendingOrders.length > 0) {
    openModal({
      title: "无法申请变更",
      body: `
        <p>您当前有 ${
          pendingOrders.length
        } 个未完成的服务单，请先完成或撤销这些订单后再申请变更服务地区。</p>
        <div style="margin-top: 16px;">
          <strong>未完成的订单：</strong>
          <ul style="margin: 8px 0; padding-left: 20px;">
            ${pendingOrders
              .map((order) => `<li>${order.id} - ${order.merchant}</li>`)
              .join("")}
          </ul>
        </div>
      `,
      confirmText: "我知道了",
      onConfirm: () => {
        closeModal();
      },
    });
    return;
  }

  // 获取可用的地区选项（这里可以扩展为从服务器获取）
  const availableRegions = [
    "北京市 全域",
    "上海市 全域",
    "广东省 深圳市",
    "广东省 广州市",
    "浙江省 杭州市",
    "江苏省 南京市",
    "江苏省 苏州市",
    "四川省 成都市",
    "湖北省 武汉市",
    "陕西省 西安市",
    "山东省 济南市",
    "福建省 厦门市",
  ];

  openModal({
    title: "申请变更服务地区",
    body: `
      <div style="margin-bottom: 16px;">
        <h4 style="margin: 0 0 12px 0; color: var(--color-neutral-700);">当前服务地区</h4>
        <div style="display: flex; flex-wrap: wrap; gap: 8px; margin-bottom: 16px;">
          ${state.account.regions
            .map(
              (region) => `
            <span style="background: var(--color-primary-100); color: var(--color-primary-700); padding: 4px 8px; border-radius: 4px; font-size: 12px;">
              ${region.name} ${
                region.status === "active" ? "(生效中)" : "(待审核)"
              }
            </span>
          `
            )
            .join("")}
        </div>
      </div>
      
      <div style="display: grid; grid-template-columns: repeat(2, 1fr); gap: 16px;">
        <div>
          <h4 style="margin: 0 0 12px 0; color: var(--color-neutral-700);">新增服务地区</h4>
          <div style="max-height: 200px; overflow-y: auto; border: 1px solid var(--color-neutral-200); border-radius: 6px; padding: 8px;">
            ${availableRegions
              .filter(
                (region) =>
                  !state.account.regions.some((r) => r.name === region)
              )
              .map(
                (region) => `
              <label style="display: flex; align-items: center; padding: 8px; cursor: pointer; border-radius: 4px; margin-bottom: 4px;">
                <input type="checkbox" value="${region}" style="margin-right: 8px;" />
                <span>${region}</span>
              </label>
            `
              )
              .join("")}
          </div>
        </div>
        
        <div>
          <h4 style="margin: 0 0 12px 0; color: var(--color-neutral-700);">移除服务地区</h4>
          <div style="max-height: 200px; overflow-y: auto; border: 1px solid var(--color-neutral-200); border-radius: 6px; padding: 8px;">
            ${state.account.regions
              .filter((region) => region.status === "active")
              .map(
                (region) => `
              <label style="display: flex; align-items: center; padding: 8px; cursor: pointer; border-radius: 4px; margin-bottom: 4px;">
                <input type="checkbox" value="${region.name}" style="margin-right: 8px;" />
                <span>${region.name}</span>
              </label>
            `
              )
              .join("")}
          </div>
        </div>
      </div>
      
      <div style="margin-top: 16px; padding: 12px; background: var(--color-warning-100); border-radius: 6px; border-left: 4px solid var(--color-warning-500);">
        <strong>注意事项：</strong>
        <ul style="margin: 8px 0; padding-left: 20px; font-size: 14px;">
          <li>新增地区需要平台审核通过后才能生效</li>
          <li>移除地区将影响该地区的服务单接收</li>
          <li>审核结果将通过消息中心通知</li>
        </ul>
      </div>
    `,
    confirmText: "提交申请",
    onConfirm: () => {
      // 获取新增的地区
      const newRegions = Array.from(
        document.querySelectorAll('input[type="checkbox"]:checked')
      )
        .filter(
          (input) => !state.account.regions.some((r) => r.name === input.value)
        )
        .map((input) => input.value);

      // 获取要移除的地区
      const removeRegions = Array.from(
        document.querySelectorAll('input[type="checkbox"]:checked')
      )
        .filter((input) =>
          state.account.regions.some((r) => r.name === input.value)
        )
        .map((input) => input.value);

      if (newRegions.length === 0 && removeRegions.length === 0) {
        showToast("请选择要新增或移除的服务地区", "warning");
        return false;
      }

      // 添加新地区
      newRegions.forEach((region) => {
        state.account.regions.push({ name: region, status: "pending" });
      });

      // 移除地区（这里只是标记为待移除，实际移除需要审核）
      removeRegions.forEach((regionName) => {
        const region = state.account.regions.find((r) => r.name === regionName);
        if (region) {
          region.status = "removing";
        }
      });

      const changes = [];
      if (newRegions.length > 0) {
        changes.push(`新增 ${newRegions.length} 个地区`);
      }
      if (removeRegions.length > 0) {
        changes.push(`移除 ${removeRegions.length} 个地区`);
      }

      state.account.pendingMessage = `您的服务地区变更申请已提交（${changes.join(
        "，"
      )}），平台将在 24 小时内审核`;
      showToast("服务地区变更申请已提交，请等待审核", "success");
      closeModal();
      renderAccount();
    },
  });
}

function handleAccountAddRegion() {
  // 保留原有功能作为备用
  openModal({
    title: "新增服务区域",
    body: `
      <p>输入拟新增的服务区域（例如：广东省 深圳市）：</p>
      <input id="new-region" type="text" style="width:100%; padding:12px; border-radius:6px; border:1px solid var(--color-neutral-200);" />
    `,
    confirmText: "提交审核",
    onConfirm: () => {
      const value = document.getElementById("new-region").value.trim();
      if (!value) {
        showToast("请输入服务区域", "error");
        return false;
      }
      state.account.regions.push({ name: value, status: "pending" });
      showToast(`服务区域 ${value} 已提交审核`, "success");
      closeModal();
      renderAccount();
    },
  });
}

function handleAccountRemoveRegion(name) {
  const region = state.account.regions.find((item) => item.name === name);
  if (!region) return;
  openModal({
    title: "移除服务区域",
    body: `<p>确认从服务范围中移除「${name}」？已签约商户不会受到影响。</p>`,
    confirmText: "确认移除",
    onConfirm: () => {
      state.account.regions = state.account.regions.filter(
        (item) => item.name !== name
      );
      showToast(`已移除服务区域 ${name}`, "info");
      closeModal();
      renderAccount();
    },
  });
}

function handleTeamAdd() {
  openModal({
    title: "添加员工",
    body: `
      <input id="team-name" type="text" placeholder="姓名" style="width:100%; padding:12px; border-radius:6px; border:1px solid var(--color-neutral-200);" />
      <input id="team-contact" type="text" placeholder="联系方式" style="width:100%; margin-top:12px; padding:12px; border-radius:6px; border:1px solid var(--color-neutral-200);" />
      <select id="team-role" style="width:100%; margin-top:12px; padding:12px; border-radius:6px; border:1px solid var(--color-neutral-200);">
        <option value="">选择角色</option>
        <option value="管理员">管理员</option>
        <option value="维修师傅">维修师傅</option>
      </select>
    `,
    confirmText: "创建账号",
    onConfirm: () => {
      const name = document.getElementById("team-name").value.trim();
      const contact = document.getElementById("team-contact").value.trim();
      const role = document.getElementById("team-role").value;
      if (!name || !contact || !role) {
        showToast("请填写完整员工信息", "error");
        return false;
      }
      state.team.push({
        id: `T-${Math.floor(Math.random() * 900 + 100)}`,
        name,
        contact,
        role,
        status: "active",
      });
      showToast(`已创建员工账号 ${name}`, "success");
      closeModal();
      renderTeam();
    },
  });
}

function handleTeamStatus(memberId, nextStatus) {
  const member = state.team.find((item) => item.id === memberId);
  if (!member) return;
  member.status = nextStatus;
  showToast(
    `员工 ${member.name} 已${nextStatus === "active" ? "恢复" : "暂停"}`,
    "info"
  );
  renderTeam();
}

function handleTeamDelete(memberId) {
  const member = state.team.find((item) => item.id === memberId);
  if (!member) return;
  openModal({
    title: `删除员工：${member.name}`,
    body: "<p>确认删除该员工账号？删除后将无法恢复。</p>",
    confirmText: "删除",
    onConfirm: () => {
      state.team = state.team.filter((item) => item.id !== memberId);
      showToast(`已删除员工 ${member.name}`, "info");
      closeModal();
      renderTeam();
    },
  });
}

function handleNotificationOpen(noticeId) {
  const notice = state.notifications.find((item) => item.id === noticeId);
  if (!notice) return;
  notice.read = true;
  showToast("已打开通知并标记为已读", "info");
  renderNotifications();
  if (notice.route) activateRoute(notice.route);
}

function handleNotificationRead(noticeId) {
  const notice = state.notifications.find((item) => item.id === noticeId);
  if (!notice) return;
  notice.read = true;
  showToast("通知已标记为已读", "success");
  renderNotifications();
}

function handleOrdersFilter(filter) {
  state.ordersFilter = filter;
  renderOrders();
}

function handleOrdersSearch(value) {
  state.ordersSearch = value.trim();
  renderOrders();
}

function handleOrdersReset() {
  state.ordersFilter = "pending_confirm";
  state.ordersSearch = "";
  state.ordersWaybillSearch = "";
  els.ordersSearch.value = "";
  const waybillInput = document.getElementById("orders-waybill");
  if (waybillInput) waybillInput.value = "";
  renderOrders();
}

// 新增：按快递单号查询服务单（用例035）
function handleWaybillSearch() {
  const waybillInput = document.getElementById("orders-waybill");
  const waybill = waybillInput ? waybillInput.value.trim() : "";
  if (!waybill) {
    showToast("请输入快递单号", "warning");
    return;
  }
  const order = state.orders.find((o) => o.waybillNumber === waybill);
  if (order) {
    state.ordersWaybillSearch = waybill;
    handleOrderDetail(order.id);
  } else {
    showToast("未找到对应的服务单，请检查快递单号", "error");
  }
}

function handleTeamSearch(value) {
  state.teamSearch = value.trim();
  renderTeam();
}

function handleTeamStatusFilter(value) {
  state.teamStatusFilter = value;
  renderTeam();
}

function handleTeamRoleFilter(value) {
  state.teamRoleFilter = value;
  renderTeam();
}

function handleTeamReset() {
  state.teamSearch = "";
  state.teamStatusFilter = "all";
  state.teamRoleFilter = "all";
  els.teamSearch.value = "";
  els.teamStatusFilter.value = "all";
  els.teamRoleFilter.value = "all";
  renderTeam();
}

function registerEventListeners() {
  els.authShowSignup.forEach((btn) =>
    btn.addEventListener("click", () => showAuth("signup"))
  );
  els.authShowLogin.forEach((btn) =>
    btn.addEventListener("click", () => showAuth("login"))
  );

  els.navItems.forEach((item) => {
    item.addEventListener("click", () => {
      if (!state.isAuthenticated) {
        showToast("请先登录以访问控制台", "warning");
        showAuth("login");
        return;
      }
      activateRoute(item.dataset.route);
    });
  });

  els.ordersFilters.addEventListener("click", (event) => {
    const target = event.target.closest("[data-filter]");
    if (!target) return;
    handleOrdersFilter(target.dataset.filter);
  });

  els.ordersSearch.addEventListener("input", (event) =>
    handleOrdersSearch(event.target.value)
  );
  els.ordersReset.addEventListener("click", handleOrdersReset);

  // 快递单号查询按钮事件绑定
  const waybillSearchBtn = document.getElementById("orders-waybill-search");
  if (waybillSearchBtn) {
    waybillSearchBtn.addEventListener("click", handleWaybillSearch);
  }

  els.teamSearch.addEventListener("input", (event) =>
    handleTeamSearch(event.target.value)
  );
  els.teamStatusFilter.addEventListener("change", (event) =>
    handleTeamStatusFilter(event.target.value)
  );
  els.teamRoleFilter.addEventListener("change", (event) =>
    handleTeamRoleFilter(event.target.value)
  );
  els.teamReset.addEventListener("click", handleTeamReset);

  document.addEventListener("click", (event) => {
    const actionBtn = event.target.closest("[data-action]");
    if (!actionBtn) return;
    const action = actionBtn.dataset.action;
    const orderId = actionBtn.dataset.order;
    const contractId = actionBtn.dataset.contract;
    const memberId = actionBtn.dataset.member;
    const regionName = actionBtn.dataset.region;
    const fileName = actionBtn.dataset.file;
    const noticeId = actionBtn.dataset.notice;

    const authRequired = new Set([
      "order-detail",
      "order-accept",
      "order-receive",
      "order-complete",
      "order-cancel",
      "contract-open",
      "contract-confirm",
      "contract-reject",
      "contract-download",
      "contract-suspend",
      "contract-restore",
      "contract-cancel",
      "contract-new-request",
      "contract-search",
      "contract-reset",
      "account-edit",
      "account-change-regions",
      "account-add-region",
      "account-remove-region",
      "account-upload-file",
      "account-preview-file",
      "account-update-file",
      "team-add",
      "team-import",
      "team-pause",
      "team-resume",
      "team-delete",
      "notification-open",
      "notification-read",
    ]);

    if (authRequired.has(action) && !state.isAuthenticated) {
      showToast("请先登录以执行该操作", "warning");
      showAuth("login");
      return;
    }

    switch (action) {
      case "forget-password":
        showToast("密码重置链接已发送至注册邮箱（示例）", "info");
        break;
      case "order-detail":
        handleOrderDetail(orderId);
        break;
      case "order-accept":
        handleOrderAccept(orderId);
        break;
      case "order-receive":
        handleOrderReceive(orderId);
        break;
      case "order-complete":
        handleOrderComplete(orderId);
        break;
      case "order-cancel":
        handleOrderCancel(orderId);
        break;
      case "order-reject":
        handleOrderReject(orderId);
        break;
      case "order-assign":
        handleOrderAssign(orderId);
        break;
      case "order-reassign":
        handleOrderReassign(orderId);
        break;
      case "order-onsite":
        handleOrderOnsite(orderId);
        break;
      case "order-return":
        handleOrderReturn(orderId);
        break;
      case "contract-open":
        openContractDetail(contractId);
        break;
      case "contract-confirm":
        confirmContract(contractId);
        break;
      case "contract-reject":
        rejectContract(contractId);
        break;
      case "contract-download":
        downloadContract(contractId);
        break;
      case "contract-suspend":
        suspendContract(contractId);
        break;
      case "contract-restore":
        restoreContract(contractId);
        break;
      case "contract-cancel":
        cancelContract(contractId);
        break;
      case "contract-new-request":
        showToast(
          "请联系运营提交新合同申请，后续版本将接入在线提交流程",
          "info"
        );
        break;
      case "contract-search":
        handleContractSearchSubmit();
        break;
      case "contract-reset":
        handleContractReset();
        break;
      case "account-edit":
        handleAccountEdit();
        break;
      case "account-change-regions":
        handleAccountChangeRegions();
        break;
      case "account-add-region":
        handleAccountAddRegion();
        break;
      case "account-remove-region":
        handleAccountRemoveRegion(regionName);
        break;
      case "account-upload-file":
        showToast("请在新窗口上传资质文件（示例）", "info");
        break;
      case "account-preview-file":
        showToast(`预览文件 ${fileName}`, "info");
        break;
      case "account-update-file":
        showToast(`已提交 ${fileName} 更新申请`, "success");
        break;
      case "team-add":
        handleTeamAdd();
        break;
      case "team-import":
        showToast("暂未接入批量导入，可下载模板后在此上传", "info");
        break;
      case "team-pause":
        handleTeamStatus(memberId, "paused");
        break;
      case "team-resume":
        handleTeamStatus(memberId, "active");
        break;
      case "team-delete":
        handleTeamDelete(memberId);
        break;
      case "notification-open":
        handleNotificationOpen(noticeId);
        break;
      case "notification-read":
        handleNotificationRead(noticeId);
        break;
      default:
        break;
    }
  });
  if (els.contractStatusTabs) {
    els.contractStatusTabs.addEventListener("click", (event) => {
      const btn = event.target.closest("[data-contract-status]");
      if (!btn) return;
      setContractView(btn.dataset.contractStatus);
    });
  }
  if (els.contractFilterForm) {
    els.contractFilterForm.addEventListener(
      "submit",
      handleContractSearchSubmit
    );
  }

  els.modalCancel.addEventListener("click", closeModal);
  els.modalConfirm.addEventListener("click", () => {
    if (typeof modalConfirmHandler === "function") {
      const keepOpen = modalConfirmHandler() === false;
      if (!keepOpen) closeModal();
    } else {
      closeModal();
    }
  });
}

function initialize() {
  initData();
  registerEventListeners();
  renderLogin();
  renderSignup();
  showAuth("login");
  renderDashboard();
  renderOrders();
  renderContracts();
  renderTeam();
  renderAccount();
  renderNotifications();
}

initialize();
activateRoute("login");
