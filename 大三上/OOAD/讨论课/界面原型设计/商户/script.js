const ROUTE_LABELS = {
  account: "账号与员工",
  product: "商品与销售",
  order: "订单履约",
  aftersale: "售后处理",
  finance: "交易与对账",
  service: "服务目录",
  partner: "合作伙伴与合同",
  activity: "活动中心",
};

const TAB_DEFAULTS = {
  account: "account-profile",
  product: "product-items",
  finance: "finance-payment",
  partner: "partner-providers",
  activity: "activity-promo",
};

const ORDER_STATUS_META = {
  unpaid: { label: "未支付", tone: "info" },
  awaiting_accept: { label: "待接受", tone: "info" },
  awaiting_ship: { label: "待发货", tone: "warning" },
  shipped: { label: "运输中", tone: "info" },
  finished: { label: "已完成", tone: "success" },
  cancelled: { label: "已取消", tone: "danger" },
};

const AFTERSALE_STATUS_META = {
  0: { label: "待审核", tone: "warning" },
  1: { label: "待验收", tone: "info" },
  2: { label: "待上门", tone: "info" },
  3: { label: "已取消", tone: "danger" },
  4: { label: "已验收", tone: "success" },
  5: { label: "维修中", tone: "warning" },
  6: { label: "已完成", tone: "success" },
  // 兼容旧的字符串key
  pending_review: { label: "待审核", tone: "warning" },
  in_progress: { label: "处理中", tone: "info" },
  waiting_receipt: { label: "待收货", tone: "warning" },
  finished: { label: "已完成", tone: "success" },
};

const PRODUCT_STATUS_META = {
  approved: { label: "已核准", tone: "success" },
  pending: { label: "审核中", tone: "info" },
  rejected: { label: "未通过", tone: "danger" },
};

const SALES_TYPE_META = [
  { id: "normal", label: "普通销售" },
  { id: "presale", label: "预售" },
  { id: "group", label: "团购" },
];

const ORDER_STATUS_STRIP = [
  { id: "unpaid", label: "未支付" },
  { id: "awaiting_accept", label: "待接受" },
  { id: "awaiting_ship", label: "待发货" },
  { id: "shipped", label: "运输中" },
  { id: "finished", label: "已完成" },
  { id: "cancelled", label: "已取消" },
];

const AFTERSALE_FILTERS = [
  { id: "0", label: "待审核" },
  { id: "1", label: "待验收" },
  { id: "2", label: "待上门" },
  { id: "4", label: "已验收" },
  { id: "5", label: "维修中" },
  { id: "6", label: "已完成" },
  { id: "3", label: "已取消" },
  // 兼容旧定义
  { id: "pending_review", label: "待审核", hidden: true },
  { id: "in_progress", label: "处理中", hidden: true },
  { id: "waiting_receipt", label: "待收货" },
  { id: "finished", label: "已完成" },
];

const TOAST_DURATION = 3200;

const state = {
  route: "account",
  tabs: { ...TAB_DEFAULTS },
  isAdmin: false,
  staffFilters: { keyword: "", status: "all", role: "all" },
  productFilters: { keyword: "", status: "all", type: "all" },
  salesType: "normal",
  salesFilters: { keyword: "", start: "", end: "", status: "all" },
  orderFilters: {
    status: "awaiting_accept",
    keyword: "",
    date: "",
    region: "",
    phone: "",
  },
  aftersaleFilters: {
    status: "0",
    keyword: "",
    type: "all",
    phone: "",
    waybill: "",
  },
  paymentFilters: { channel: "all", keyword: "", date: "", amount: "" },
  refundFilters: { keyword: "", date: "", amount: "" },
  // 活动筛选
  promoKeyword: "",
  promoStatus: "all",
  promoStart: "",
  promoEnd: "",
  promoProduct: "",
  groupKeyword: "",
  groupStart: "",
  groupEnd: "",
  assign: { activityId: null, productIds: [] },
  serviceFilters: {
    keyword: "",
    type: "",
    product: "",
    status: "all",
    region: "",
  },
};

const accountDefaults = {
  name: "星河数码旗舰店",
  category: "3C数码",
  contact: "赵一宁",
  phone: "13612345678",
  email: "merchant@oomall.com",
  address: "上海市虹口区嘉兴路 88 号",
};

const accountState = {
  profile: { ...accountDefaults },
  quotas: {
    productLimit: 500,
    productUsed: 386,
    staffLimit: 200,
    freeShipping: 99,
    riskStatus: "正常",
    riskTone: "success",
    riskHint: "最近 30 日无异常交易",
  },
  quotasPending: null,
  openingPending: null,
  cancelPending: false,
};

const accountApprovals = [
  { time: "2025-10-14 09:30", subject: "免邮门槛调整", status: "已通过" },
  { time: "2025-10-12 11:05", subject: "经营类目变更", status: "已通过" },
  { time: "2025-10-08 18:15", subject: "风控自动巡检", status: "正常" },
];

const accountData = {
  timeline: [
    {
      time: "2025-10-14 15:30",
      content: "管理员修改免邮门槛，提交审核",
      actor: "系统",
    },
    {
      time: "2025-10-12 11:05",
      content: "平台通过经营类目变更申请",
      actor: "平台审核",
    },
    {
      time: "2025-10-10 09:42",
      content: "新增员工：李妍（客服）",
      actor: "管理员",
    },
    {
      time: "2025-10-08 18:15",
      content: "系统提醒：员工账号已使用 60%",
      actor: "系统",
    },
  ],
};

const accountFieldLabels = {
  name: "商户名称",
  category: "经营类目",
  contact: "联系人",
  phone: "联系电话",
  email: "联系邮箱",
  address: "经营地址",
};

let accountProfileInitialized = false;

function formatDateTime(date = new Date()) {
  const pad = (num) => String(num).padStart(2, "0");
  return `${date.getFullYear()}-${pad(date.getMonth() + 1)}-${pad(
    date.getDate()
  )} ${pad(date.getHours())}:${pad(date.getMinutes())}`;
}

function countActiveStaff() {
  return staffData.filter((staff) => staff.status === "active").length;
}

function getAccountFieldElements() {
  return {
    name: document.getElementById("account-name"),
    category: document.getElementById("account-category"),
    contact: document.getElementById("account-contact"),
    phone: document.getElementById("account-phone"),
    email: document.getElementById("account-email"),
    address: document.getElementById("account-address"),
  };
}

function renderAccountProfileFields() {
  const fields = getAccountFieldElements();
  if (!fields.name) return;
  if (fields.name) fields.name.value = accountState.profile.name || "";
  if (fields.category)
    fields.category.value = accountState.profile.category || "3C数码";
  if (fields.contact) fields.contact.value = accountState.profile.contact || "";
  if (fields.phone) fields.phone.value = accountState.profile.phone || "";
  if (fields.email) fields.email.value = accountState.profile.email || "";
  if (fields.address) fields.address.value = accountState.profile.address || "";
}

function updateAccountMetrics() {
  const {
    productLimit,
    productUsed,
    staffLimit,
    freeShipping,
    riskStatus,
    riskHint,
    riskTone,
  } = accountState.quotas;
  const productLimitEl = document.getElementById("quota-product-limit");
  if (productLimitEl) productLimitEl.textContent = productLimit;
  const productUsageEl = document.getElementById("quota-product-usage");
  if (productUsageEl) productUsageEl.textContent = `已上架 ${productUsed} 件`;
  const staffLimitEl = document.getElementById("quota-staff-limit");
  if (staffLimitEl) staffLimitEl.textContent = staffLimit;
  const staffActive = countActiveStaff();
  const staffUsageEl = document.getElementById("quota-staff-usage");
  if (staffUsageEl) staffUsageEl.textContent = `已启用 ${staffActive} 个账号`;
  const staffRateEl = document.getElementById("quota-staff-rate");
  if (staffRateEl) {
    if (staffLimit > 0) {
      const rate = Math.min(100, Math.round((staffActive / staffLimit) * 100));
      staffRateEl.textContent = `使用率 ${rate}%`;
    } else {
      staffRateEl.textContent = "暂无额度";
    }
  }
  const freeShippingEl = document.getElementById("quota-free-shipping");
  if (freeShippingEl)
    freeShippingEl.textContent = `¥ ${Number(freeShipping).toFixed(2)}`;
  const riskBadge = document.getElementById("quota-risk-status");
  if (riskBadge) {
    const toneClass =
      riskTone === "warning"
        ? "badge--warning"
        : riskTone === "danger"
        ? "badge--danger"
        : riskTone === "info"
        ? "badge--info"
        : "badge--success";
    riskBadge.className = `badge ${toneClass}`;
    riskBadge.textContent = riskStatus;
  }
  const riskHintEl = document.getElementById("quota-risk-hint");
  if (riskHintEl) riskHintEl.textContent = riskHint;
  const logCountEl = document.getElementById("account-log-count");
  if (logCountEl)
    logCountEl.textContent = `${accountData.timeline.length} 条记录`;
}

function renderAccountTimeline() {
  if (!els.accountTimeline) return;
  els.accountTimeline.innerHTML = accountData.timeline
    .map(
      (item) => `
        <li>
          <time>${item.time}</time>
          <div>${item.content}</div>
          <span class="tag tag--info">${item.actor}</span>
        </li>`
    )
    .join("");
}

function appendAccountLog(content, actor = "管理员") {
  accountData.timeline.unshift({
    time: formatDateTime(),
    content,
    actor,
  });
  if (accountData.timeline.length > 40) {
    accountData.timeline.pop();
  }
  renderAccountTimeline();
  updateAccountMetrics();
}

function collectAccountFormValues() {
  const fields = getAccountFieldElements();
  return {
    name: fields.name ? fields.name.value.trim() : "",
    category: fields.category ? fields.category.value : "",
    contact: fields.contact ? fields.contact.value.trim() : "",
    phone: fields.phone ? fields.phone.value.trim() : "",
    email: fields.email ? fields.email.value.trim() : "",
    address: fields.address ? fields.address.value.trim() : "",
  };
}

function diffAccountFields(next) {
  const diffs = [];
  for (const key of Object.keys(accountFieldLabels)) {
    const prevValue = accountState.profile[key] || "";
    const nextValue = next[key] || "";
    if (prevValue !== nextValue) {
      diffs.push({
        key,
        label: accountFieldLabels[key],
        from: prevValue || "（空）",
        to: nextValue || "（空）",
      });
    }
  }
  return diffs;
}

function openAccountQuickSave() {
  const next = collectAccountFormValues();
  const changes = diffAccountFields(next);
  if (!changes.length) {
    showToast("当前信息已是最新，无需保存", "info");
    return;
  }
  accountState.profile = { ...accountState.profile, ...next };
  accountProfileInitialized = false;
  appendAccountLog(
    `保存账号信息草稿：${changes.map((item) => item.label).join("、")}`
  );
  showToast("已保存变更草稿", "success");
  renderAccount({ syncFields: true });
}

function openAccountResetDialog() {
  openModal({
    title: "恢复上次保存内容",
    body: "<p>将撤销未提交的修改，恢复为上次保存的账号信息。</p>",
    confirmText: "确认恢复",
    onConfirm: () => {
      accountProfileInitialized = false;
      renderAccount({ syncFields: true });
      appendAccountLog("恢复账号信息到上次保存版本");
      showToast("已恢复到上次保存的版本", "info");
    },
  });
}

function openAccountSubmitDialog() {
  const next = collectAccountFormValues();
  const changes = diffAccountFields(next);
  if (!changes.length) {
    showToast("未检测到任何改动，无法提交", "info");
    return;
  }
  const listHtml = changes
    .map(
      (item) =>
        `<li>• ${item.label}：<strong>${item.from}</strong> → <strong>${item.to}</strong></li>`
    )
    .join("");
  openModal({
    title: "提交信息变更",
    body: `
      <div class="modal-section">
        <div class="modal-section__title">变更内容</div>
        <ul class="modal-list">${listHtml}</ul>
        <p class="modal-section__minor">提交后进入平台审核流程，请保持电话畅通。</p>
      </div>`,
    confirmText: "提交审核",
    onConfirm: () => {
      accountState.profile = { ...accountState.profile, ...next };
      accountProfileInitialized = false;
      accountApprovals.unshift({
        time: formatDateTime(),
        subject: "账号信息变更",
        status: "待审核",
      });
      if (accountApprovals.length > 20) {
        accountApprovals.pop();
      }
      appendAccountLog(
        `提交信息变更：${changes.map((item) => item.label).join("、")}`
      );
      showToast("变更申请已提交，待平台审核", "success");
      renderAccount({ syncFields: true });
    },
  });
}

function openAccountAuditViewer() {
  const records = accountApprovals
    .map((item) => `<li>• ${item.time} · ${item.subject} · ${item.status}</li>`)
    .join("");
  openModal({
    title: "审批记录",
    body: `
      <div class="modal-section">
        <div class="modal-section__title">历史记录</div>
        <ul class="modal-list">${records || "<li>• 暂无审批记录</li>"}</ul>
      </div>`,
    confirmText: "关闭",
    cancelText: "取消",
  });
}

function openQuotaDialog() {
  if (!state.isAdmin) {
    showToast("仅管理员可操作额度与免邮门槛调整", "warning");
    return;
  }
  const { productLimit, staffLimit, freeShipping } = accountState.quotas;
  const body = `
    <div class=\"modal-section\">
      <div class=\"modal-section__title\">额度设置</div>
      <label class=\"form-field\">
        <span>可售商品数上限</span>
        <input type=\"number\" id=\"quota-product-input\" min=\"0\" value=\"${productLimit}\" />
      </label>
      <label class=\"form-field\">
        <span>员工账号上限</span>
        <input type=\"number\" id=\"quota-staff-input\" min=\"0\" value=\"${staffLimit}\" />
      </label>
      <label class=\"form-field\">
        <span>免邮门槛（元）</span>
        <input type=\"number\" id=\"quota-free-input\" min=\"0\" step=\"1\" value=\"${freeShipping}\" />
      </label>
      <p class=\"modal-section__minor\">提交后进入审批流程，通过前不会影响现有额度和门槛。</p>
    </div>`;
  openModal({
    title: "提交额度与免邮门槛变更申请",
    body,
    confirmText: "提交审核",
    onConfirm: () => {
      const productInput = document.getElementById("quota-product-input");
      const staffInput = document.getElementById("quota-staff-input");
      const freeInput = document.getElementById("quota-free-input");
      const productValue = Number(productInput?.value);
      const staffValue = Number(staffInput?.value);
      const freeValue = Number(freeInput?.value);
      const nextProductLimit = Number.isNaN(productValue)
        ? productLimit
        : productValue;
      const nextStaffLimit = Number.isNaN(staffValue) ? staffLimit : staffValue;
      const nextFreeShipping = Number.isNaN(freeValue)
        ? freeShipping
        : freeValue;
      const staffActive = countActiveStaff();
      if (nextStaffLimit < staffActive) {
        showToast(
          `当前已启用 ${staffActive} 个账号，额度不得低于该数`,
          "warning"
        );
        return false;
      }
      if (nextProductLimit < accountState.quotas.productUsed) {
        showToast(
          `当前已上架 ${accountState.quotas.productUsed} 件商品，额度不得低于该数`,
          "warning"
        );
        return false;
      }
      // 进入审批，不立即生效
      accountState.quotasPending = {
        submittedAt: formatDateTime(),
        fields: {
          productLimit: nextProductLimit,
          staffLimit: nextStaffLimit,
          freeShipping: nextFreeShipping,
        },
      };
      accountApprovals.unshift({
        time: formatDateTime(),
        subject: "额度/免邮门槛调整",
        status: "待审核",
      });
      if (accountApprovals.length > 50) accountApprovals.pop();
      appendAccountLog("提交额度与免邮门槛变更申请");
      showToast("已提交审核，待平台审批", "success");
      updateQuotaPendingNotice();
    },
  });
}

// --- Admin gating & quota pending helpers ---
function updateQuotaPendingNotice() {
  const el = document.getElementById("quota-pending-notice");
  if (!el) return;
  const pending = accountState.quotasPending;
  if (pending && pending.fields) {
    const f = pending.fields;
    el.innerHTML =
      `已提交额度/免邮门槛变更申请（${pending.submittedAt}） · 待审核<br/>` +
      `商品上限 → ${f.productLimit} · 员工上限 → ${
        f.staffLimit
      } · 免邮门槛 → ¥ ${Number(f.freeShipping).toFixed(2)}`;
    el.classList.remove("hidden");
  } else {
    el.classList.add("hidden");
    el.textContent = "";
  }
}

function toggleAdmin() {
  state.isAdmin = !state.isAdmin;
  showToast(
    state.isAdmin ? "已切换为管理员视角" : "已切换为普通视角",
    state.isAdmin ? "success" : "info"
  );
}

// --- Account opening wizard ---
function openAccountOpenWizard() {
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">开户信息</div>
      <label class="form-field">
        <span>商户名称 *</span>
        <input id="open-name" type="text" placeholder="请输入商户名称" />
      </label>
      <label class="form-field">
        <span>经营类目 *</span>
        <select id="open-category">
          <option value="3C数码">3C数码</option>
          <option value="家电">家电</option>
          <option value="家居">家居</option>
        </select>
      </label>
      <label class="form-field">
        <span>联系人 *</span>
        <input id="open-contact" type="text" placeholder="请输入联系人" />
      </label>
      <label class="form-field">
        <span>联系电话 *</span>
        <input id="open-phone" type="tel" placeholder="11位手机号" />
      </label>
      <label class="form-field">
        <span>联系邮箱</span>
        <input id="open-email" type="email" placeholder="example@domain.com" />
      </label>
      <label class="form-field">
        <span>经营地址</span>
        <input id="open-address" type="text" placeholder="详细地址" />
      </label>
      <p class="modal-section__minor">提交后进入平台审核，预计1-2个工作日完成。审核通过前无法进行经营操作。</p>
    </div>`;
  openModal({
    title: "提交开户申请",
    body,
    confirmText: "提交申请",
    onConfirm: () => {
      const name = document.getElementById("open-name")?.value.trim();
      const category = document.getElementById("open-category")?.value;
      const contact = document.getElementById("open-contact")?.value.trim();
      const phone = document.getElementById("open-phone")?.value.trim();
      const email = document.getElementById("open-email")?.value.trim();
      const address = document.getElementById("open-address")?.value.trim();
      if (!name || !category || !contact || !phone) {
        showToast("请填写带 * 的必填项", "warning");
        return false;
      }
      accountState.openingPending = {
        submittedAt: formatDateTime(),
        fields: { name, category, contact, phone, email, address },
      };
      accountApprovals.unshift({
        time: formatDateTime(),
        subject: "开户申请",
        status: "待审核",
      });
      if (accountApprovals.length > 50) accountApprovals.pop();
      appendAccountLog(`提交开户申请：${name}`);
      showToast("开户申请已提交，待平台审核", "success");
    },
  });
}

// --- Account cancellation with unsettled check ---
function hasUnsettledSplits() {
  const p = (paymentData || []).some((it) =>
    String(it.share || "").includes("待")
  );
  const r = (refundData || []).some((it) =>
    String(it.share || "").includes("待")
  );
  return p || r;
}

function openAccountCancelDialog() {
  if (hasUnsettledSplits()) {
    const pendingPays = (paymentData || []).filter((it) =>
      String(it.share || "").includes("待")
    );
    const pendingRefs = (refundData || []).filter((it) =>
      String(it.share || "").includes("待")
    );
    const list = [
      ...pendingPays.map(
        (it) => `• 支付 ${it.id} · ${it.amount} · ${it.share}`
      ),
      ...pendingRefs.map(
        (it) => `• 退款 ${it.id} · ${it.amount} · ${it.share}`
      ),
    ].join("<br/>");
    openModal({
      title: "无法提交销户申请",
      body: `<div class="modal-section"><div class="modal-section__title">存在未结算分账/退分账</div><p>请先完成以下记录的分账处理：</p><p>${
        list || "—"
      }</p></div>`,
      confirmText: "知道了",
      cancelText: " ",
    });
    return;
  }
  openModal({
    title: "申请销户",
    body: `<div class="modal-section"><p>确认提交销户申请吗？平台将进行审核并在结清所有账务后处理。</p><p class="modal-section__minor">提示：销户后账号不可恢复，请谨慎操作。</p></div>`,
    confirmText: "提交审核",
    onConfirm: () => {
      accountState.cancelPending = true;
      accountApprovals.unshift({
        time: formatDateTime(),
        subject: "销户申请",
        status: "待审核",
      });
      if (accountApprovals.length > 50) accountApprovals.pop();
      appendAccountLog("提交销户申请");
      showToast("销户申请已提交，待平台审核", "success");
      renderAccount();
    },
  });
}

function exportAccountLog() {
  appendAccountLog("导出账号操作日志");
  showToast("操作日志已导出为 CSV", "success");
}

function openStaffCreateModal() {
  if (staffData.length >= accountState.quotas.staffLimit) {
    showToast("员工账号数量已达到当前额度，请先调整上限", "warning");
    return;
  }
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">基本信息</div>
      <label class="form-field">
        <span>姓名 *</span>
        <input type="text" id="new-staff-name" placeholder="请输入姓名" />
      </label>
      <label class="form-field">
        <span>手机号 *</span>
        <input type="tel" id="new-staff-phone" placeholder="请输入手机号" />
      </label>
      <label class="form-field">
        <span>角色</span>
        <select id="new-staff-role">
          <option value="管理员">管理员</option>
          <option value="运营">运营</option>
          <option value="客服">客服</option>
        </select>
      </label>
    </div>`;
  openModal({
    title: "新增员工账号",
    body,
    confirmText: "创建账号",
    onConfirm: () => {
      const name = document.getElementById("new-staff-name")?.value.trim();
      const phone = document.getElementById("new-staff-phone")?.value.trim();
      const role = document.getElementById("new-staff-role")?.value || "运营";
      if (!name || !phone) {
        showToast("请填写完整的姓名和手机号", "warning");
        return false;
      }
      const newId = `EMP-${String(staffData.length + 1).padStart(3, "0")}`;
      staffData.unshift({
        id: newId,
        name,
        phone,
        role,
        status: "active",
        last: formatDateTime(),
      });
      appendAccountLog(`新增员工：${name}（${role}）`);
      showToast(`已新增员工 ${name}`, "success");
      renderStaffTable();
      updateAccountMetrics();
    },
  });
}

function openStaffImportGuide() {
  openModal({
    title: "导入员工账号",
    body: `
      <div class="modal-section">
        <div class="modal-section__title">操作提示</div>
        <p>请下载 CSV 模板并填写姓名、手机号、角色，上传后系统将自动创建账号并发送初始密码。</p>
        <ul class="modal-list">
          <li>• 支持导入最多 100 条记录</li>
          <li>• 手机号将作为登录账号，请确保唯一</li>
          <li>• 角色字段支持：管理员 / 运营 / 客服</li>
        </ul>
      </div>`,
    confirmText: "下载模板",
    cancelText: "取消",
    onConfirm: () => {
      appendAccountLog("下载员工账号 CSV 模板");
      showToast("已下载员工导入模板", "success");
    },
  });
}

function confirmStaffStatusChange(id, status) {
  const staff = staffData.find((item) => item.id === id);
  if (!staff) return;
  const isSuspend = status === "suspended";
  openModal({
    title: isSuspend ? "暂停员工账号" : "恢复员工账号",
    body: `<p>确认${isSuspend ? "暂停" : "恢复"}员工 <strong>${
      staff.name
    }</strong> (${staff.role}) 吗？</p>${
      isSuspend
        ? '<p class="modal-section__minor">暂停后该员工将无法登录后台。</p>'
        : ""
    }`,
    confirmText: isSuspend ? "确认暂停" : "确认恢复",
    onConfirm: () => {
      staff.status = status;
      staff.last = formatDateTime();
      appendAccountLog(`${isSuspend ? "暂停" : "恢复"}员工：${staff.name}`);
      showToast(`员工 ${staff.name} 状态已更新`, "success");
      renderStaffTable();
      updateAccountMetrics();
    },
  });
}

function confirmStaffDeletion(id) {
  const index = staffData.findIndex((item) => item.id === id);
  if (index === -1) return;
  const staff = staffData[index];
  openModal({
    title: "删除员工账号",
    body: `<p>确认删除员工 <strong>${staff.name}</strong> (${staff.role}) 吗？</p><p class="modal-section__minor">删除后该账号将无法恢复。</p>`,
    confirmText: "确认删除",
    onConfirm: () => {
      staffData.splice(index, 1);
      appendAccountLog(`删除员工：${staff.name}`);
      showToast("已删除员工账号", "success");
      renderStaffTable();
      updateAccountMetrics();
    },
  });
}

const staffData = [
  {
    id: "EMP-001",
    name: "陈晨",
    phone: "138****8890",
    role: "管理员",
    status: "active",
    last: "2025-10-14 09:20",
  },
  {
    id: "EMP-002",
    name: "王唯",
    phone: "137****1230",
    role: "运营",
    status: "active",
    last: "2025-10-13 18:43",
  },
  {
    id: "EMP-003",
    name: "赵一",
    phone: "186****1123",
    role: "客服",
    status: "suspended",
    last: "2025-10-11 16:00",
  },
  {
    id: "EMP-004",
    name: "刘洋",
    phone: "159****7720",
    role: "运营",
    status: "active",
    last: "2025-10-12 10:15",
  },
  {
    id: "EMP-005",
    name: "许诺",
    phone: "135****9987",
    role: "客服",
    status: "active",
    last: "2025-10-10 13:35",
  },
];

const productData = [
  {
    id: "SKU-88001",
    name: "星河智能电视 75英寸",
    category: "3C数码",
    price: 6999,
    share: "18%",
    status: "approved",
    type: "standard",
    unit: "台",
    origin: "中国",
    barcode: "692880010001",
    freight: "包邮",
    logistics: "顺丰速运",
    weight: "18.5",
    sku: "SKU-88001-STD",
    attributes: {
      warranty: "三年整机保修",
      power: "180W",
    },
    pendingChange: null,
    updatedAt: "2025-10-14 10:12",
  },
  {
    id: "SKU-88002",
    name: "星河智慧家庭套装",
    category: "套装商品",
    price: 12999,
    share: "25%",
    status: "pending",
    type: "bundle",
    unit: "套",
    origin: "中国",
    barcode: "692880010002",
    freight: "包邮",
    logistics: "京东物流",
    weight: "25.0",
    sku: "SKU-88002-BUNDLE",
    attributes: {
      include: "智能音箱、智能灯具、家庭网关",
      warranty: "两年",
    },
    pendingChange: null,
    updatedAt: "2025-10-13 19:41",
  },
  {
    id: "SKU-88003",
    name: "星河空气炸锅",
    category: "厨房电器",
    price: 499,
    share: "12%",
    status: "approved",
    type: "standard",
    unit: "台",
    origin: "中国",
    barcode: "692880010003",
    freight: "满99包邮",
    logistics: "顺丰速运",
    weight: "4.2",
    sku: "SKU-88003-STD",
    attributes: {
      capacity: "4升",
      power: "1500W",
    },
    pendingChange: null,
    updatedAt: "2025-10-12 08:22",
  },
  {
    id: "SKU-88004",
    name: "星河智能洗衣机",
    category: "白色家电",
    price: 3599,
    share: "15%",
    status: "rejected",
    type: "standard",
    unit: "台",
    origin: "中国",
    barcode: "692880010004",
    freight: "包邮",
    logistics: "顺丰速运",
    weight: "60.0",
    sku: "SKU-88004-STD",
    attributes: {
      capacity: "10公斤",
      power: "2600W",
    },
    pendingChange: {
      submittedAt: "2025-10-09 14:20",
      fields: {
        category: "白色家电",
        price: 3799,
        share: "16%",
      },
      remark: "调整新能效标准价格",
    },
    updatedAt: "2025-10-11 17:05",
  },
];

const PRODUCT_CATEGORY_OPTIONS = [
  "3C数码",
  "厨房电器",
  "家居用品",
  "白色家电",
  "套装商品",
];

const PRODUCT_TYPE_OPTIONS = [
  { value: "standard", label: "普通商品" },
  { value: "bundle", label: "捆绑商品" },
];

function findProductById(productId) {
  return productData.find((item) => item.id === productId);
}

function getProductDisplayName(productId) {
  const product = findProductById(productId);
  if (!product) return productId;
  return `${product.name}（${product.id}）`;
}

function formatDateRange(start, end) {
  if (!start || !end) return "-";
  return `${start} - ${end}`;
}

function refreshProductView() {
  if (state.route === "product") {
    renderProduct();
  } else {
    renderProductItems();
  }
}

function openProductImportGuide() {
  openModal({
    title: "导入商品",
    body: `
      <div class="modal-section">
        <div class="modal-section__title">导入指南</div>
        <p>请下载平台提供的 CSV 模板，按要求填写商品基本信息（分类、名称、原价、单位、产地、条码、分账比例、SKU 等），导入后系统将进入审核流程。</p>
        <ul class="modal-list">
          <li>• 支持批量导入最多 200 条商品</li>
          <li>• 捆绑商品请在模板中标记并列出组成 SKU</li>
          <li>• 导入成功后可在“审核中”列表查看处理进度</li>
        </ul>
      </div>
    `,
    confirmText: "下载模板",
    onConfirm: () => {
      showToast("已下载商品导入模板，请按照要求填写并上传", "success");
    },
  });
}

function getProductBaseFormFields(product = {}) {
  const categoryOptions = PRODUCT_CATEGORY_OPTIONS.map(
    (item) =>
      `<option value="${item}" ${
        product.category === item ? "selected" : ""
      }>${item}</option>`
  ).join("");
  const typeOptions = PRODUCT_TYPE_OPTIONS.map(
    (item) =>
      `<option value="${item.value}" ${
        product.type === item.value ? "selected" : ""
      }>${item.label}</option>`
  ).join("");
  return `
    <label class="form-field">
      <span>商品名称 *</span>
      <input type="text" id="product-form-name" value="${
        product.name || ""
      }" placeholder="请输入商品名称" />
    </label>
    <label class="form-field">
      <span>商品分类 *</span>
      <select id="product-form-category">${categoryOptions}</select>
    </label>
    <label class="form-field">
      <span>商品类型 *</span>
      <select id="product-form-type">${typeOptions}</select>
    </label>
    <label class="form-field">
      <span>原价 (¥) *</span>
      <input type="number" id="product-form-price" min="0" step="0.01" value="${
        product.price ?? ""
      }" />
    </label>
    <label class="form-field">
      <span>分账比例 *</span>
      <input type="text" id="product-form-share" value="${
        product.share || ""
      }" placeholder="例如 18%" />
    </label>
    <label class="form-field">
      <span>单位 *</span>
      <input type="text" id="product-form-unit" value="${
        product.unit || ""
      }" placeholder="台 / 个 / 套" />
    </label>
    <label class="form-field">
      <span>产地</span>
      <input type="text" id="product-form-origin" value="${
        product.origin || ""
      }" />
    </label>
    <label class="form-field">
      <span>条码</span>
      <input type="text" id="product-form-barcode" value="${
        product.barcode || ""
      }" />
    </label>
    <label class="form-field">
      <span>SKU</span>
      <input type="text" id="product-form-sku" value="${product.sku || ""}" />
    </label>
  `;
}

function getProductAttrFormFields(product = {}) {
  return `
    <label class="form-field">
      <span>运费信息</span>
      <input type="text" id="product-form-freight" value="${
        product.freight || ""
      }" placeholder="例如 满99包邮" />
    </label>
    <label class="form-field">
      <span>配送物流</span>
      <input type="text" id="product-form-logistics" value="${
        product.logistics || ""
      }" placeholder="例如 顺丰速运" />
    </label>
    <label class="form-field">
      <span>重量 (kg)</span>
      <input type="number" id="product-form-weight" min="0" step="0.1" value="${
        product.weight ?? ""
      }" />
    </label>
    <label class="form-field">
      <span>自定义属性</span>
      <textarea id="product-form-attributes" rows="3" placeholder="以 key:value 形式填写，一行一个">${formatAttributesTextarea(
        product.attributes
      )}</textarea>
    </label>
  `;
}

function formatAttributesTextarea(attributes = {}) {
  return Object.entries(attributes)
    .map(([key, value]) => `${key}:${value}`)
    .join("\n");
}

function parseAttributesTextarea(value) {
  const result = {};
  (value || "")
    .split("\n")
    .map((line) => line.trim())
    .filter(Boolean)
    .forEach((row) => {
      const [key, ...rest] = row.split(":");
      if (!key) return;
      result[key.trim()] = rest.join(":").trim();
    });
  return result;
}

function openProductCreateForm() {
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">基本信息</div>
      <div class="form-grid">
        ${getProductBaseFormFields({
          type: "standard",
          category: PRODUCT_CATEGORY_OPTIONS[0],
        })}
      </div>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">配送与属性</div>
      <div class="form-grid">
        ${getProductAttrFormFields({ freight: "包邮", logistics: "顺丰速运" })}
      </div>
    </div>
  `;
  openModal({
    title: "创建新商品",
    body,
    confirmText: "提交审核",
    onConfirm: () => {
      const name = document.getElementById("product-form-name")?.value.trim();
      const category = document.getElementById("product-form-category")?.value;
      const type = document.getElementById("product-form-type")?.value;
      const price = Number(
        document.getElementById("product-form-price")?.value
      );
      const share = document.getElementById("product-form-share")?.value.trim();
      if (!name || !category || !type || Number.isNaN(price)) {
        showToast("请完整填写商品名称、分类、类型与价格", "warning");
        return false;
      }
      const q = accountState.quotas || {};
      if (
        typeof q.productLimit === "number" &&
        typeof q.productUsed === "number" &&
        q.productUsed + 1 > q.productLimit
      ) {
        showToast("超出可售商品数上限，请先申请提升额度", "warning");
        return false;
      }
      const newProduct = {
        id: `SKU-${Date.now()}`,
        name,
        category,
        type,
        price,
        share,
        unit:
          document.getElementById("product-form-unit")?.value.trim() || "件",
        origin:
          document.getElementById("product-form-origin")?.value.trim() || "",
        barcode:
          document.getElementById("product-form-barcode")?.value.trim() || "",
        sku: document.getElementById("product-form-sku")?.value.trim() || "",
        freight:
          document.getElementById("product-form-freight")?.value.trim() ||
          "包邮",
        logistics:
          document.getElementById("product-form-logistics")?.value.trim() ||
          "顺丰速运",
        weight:
          Number(document.getElementById("product-form-weight")?.value) || 0,
        attributes: parseAttributesTextarea(
          document.getElementById("product-form-attributes")?.value
        ),
        status: "pending",
        pendingChange: null,
        updatedAt: formatDateTime(),
      };
      productData.unshift(newProduct);
      if (
        accountState.quotas &&
        typeof accountState.quotas.productUsed === "number"
      ) {
        accountState.quotas.productUsed += 1;
      }
      showToast(`商品 ${name} 已提交审核`, "success");
      refreshProductView();
    },
  });
}

function openProductEditForm(productId) {
  const product = findProductById(productId);
  if (!product) return;
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">修改商品属性</div>
      <div class="form-grid">
        ${getProductAttrFormFields(product)}
      </div>
      <p class="modal-section__minor">修改后立即生效，无需重新审核。</p>
    </div>
  `;
  openModal({
    title: `编辑属性 · ${product.name}`,
    body,
    confirmText: "保存",
    onConfirm: () => {
      product.freight =
        document.getElementById("product-form-freight")?.value.trim() ||
        product.freight;
      product.logistics =
        document.getElementById("product-form-logistics")?.value.trim() ||
        product.logistics;
      const weightValue = document.getElementById("product-form-weight")?.value;
      product.weight =
        weightValue === "" ? product.weight : Number(weightValue);
      product.attributes = parseAttributesTextarea(
        document.getElementById("product-form-attributes")?.value
      );
      product.updatedAt = formatDateTime();
      showToast(`商品 ${product.name} 属性已更新`, "success");
      refreshProductView();
    },
  });
}

function openProductChangeForm(productId) {
  const product = findProductById(productId);
  if (!product) return;
  if (product.status !== "approved") {
    showToast("仅已核准商品支持变更申请", "warning");
    return;
  }
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">变更内容</div>
      <div class="form-grid">
        ${getProductBaseFormFields(product)}
      </div>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">变更说明</div>
      <textarea id="product-form-remark" rows="3" placeholder="说明调整原因（选填）">${
        product.pendingChange?.remark || ""
      }</textarea>
    </div>
  `;
  openModal({
    title: `变更申请 · ${product.name}`,
    body,
    confirmText: "提交申请",
    onConfirm: () => {
      const priceValue = Number(
        document.getElementById("product-form-price")?.value
      );
      const shareValue = document
        .getElementById("product-form-share")
        ?.value.trim();
      if (Number.isNaN(priceValue) || !shareValue) {
        showToast("请填写完整的变更字段", "warning");
        return false;
      }
      product.pendingChange = {
        submittedAt: formatDateTime(),
        fields: {
          name:
            document.getElementById("product-form-name")?.value.trim() ||
            product.name,
          category:
            document.getElementById("product-form-category")?.value ||
            product.category,
          type:
            document.getElementById("product-form-type")?.value || product.type,
          price: priceValue,
          share: shareValue,
          unit:
            document.getElementById("product-form-unit")?.value.trim() ||
            product.unit,
          origin:
            document.getElementById("product-form-origin")?.value.trim() ||
            product.origin,
          barcode:
            document.getElementById("product-form-barcode")?.value.trim() ||
            product.barcode,
          sku:
            document.getElementById("product-form-sku")?.value.trim() ||
            product.sku,
        },
        remark:
          document.getElementById("product-form-remark")?.value.trim() || "",
      };
      product.status = "pending";
      product.updatedAt = formatDateTime();
      showToast(`商品 ${product.name} 变更申请已提交`, "success");
      refreshProductView();
    },
  });
}

function openProductDetail(productId) {
  const product = findProductById(productId);
  if (!product) return;
  const meta =
    PRODUCT_STATUS_META[product.status] || PRODUCT_STATUS_META.approved;
  const baseInfo = [
    ["商品名称", product.name],
    ["分类", product.category],
    [
      "类型",
      PRODUCT_TYPE_OPTIONS.find((item) => item.value === product.type)?.label ||
        product.type,
    ],
    ["原价", `¥ ${product.price}`],
    ["分账比例", product.share],
    ["单位", product.unit],
    ["产地", product.origin],
    ["条码", product.barcode],
    ["SKU", product.sku],
  ]
    .map((item) => `<li>• ${item[0]}：${item[1] || "—"}</li>`)
    .join("");
  const attrInfo = [
    ["运费信息", product.freight],
    ["配送物流", product.logistics],
    ["重量", product.weight ? `${product.weight} kg` : "—"],
  ]
    .map((item) => `<li>• ${item[0]}：${item[1] || "—"}</li>`)
    .join("");
  const extraAttrs = Object.entries(product.attributes || {})
    .map(([key, value]) => `<li>• ${key}：${value}</li>`)
    .join("");
  const pendingHtml = product.pendingChange
    ? `<div class="modal-section">
        <div class="modal-section__title">待审核的变更</div>
        <p class="modal-section__minor">提交时间：${
          product.pendingChange.submittedAt
        }</p>
        <ul class="modal-list">
          <li>• 价格：¥ ${product.pendingChange.fields.price}</li>
          <li>• 分账比例：${product.pendingChange.fields.share}</li>
          <li>• 分类：${product.pendingChange.fields.category}</li>
          <li>• 类型：${
            PRODUCT_TYPE_OPTIONS.find(
              (item) => item.value === product.pendingChange.fields.type
            )?.label || product.pendingChange.fields.type
          }</li>
        </ul>
        ${
          product.pendingChange.remark
            ? `<p class="modal-section__minor">说明：${product.pendingChange.remark}</p>`
            : ""
        }
      </div>`
    : "";
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">商品状态</div>
      <div>状态：<span class="status-tag status-tag--${meta.tone}">${
    meta.label
  }</span></div>
      <div class="modal-section__minor">最近更新：${product.updatedAt}</div>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">基本信息</div>
      <ul class="modal-list">${baseInfo}</ul>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">配送与属性</div>
      <ul class="modal-list">${attrInfo}${extraAttrs ? extraAttrs : ""}</ul>
    </div>
    ${pendingHtml}
  `;
  openModal({
    title: `商品详情 · ${product.name}`,
    body,
    confirmText: "关闭",
    cancelText: " ",
    onConfirm: () => {},
  });
}

const salesData = [
  {
    id: "SALE-3001",
    product: "星河智能电视 75英寸",
    type: "normal",
    price: "¥ 5999",
    start: "2025-10-20",
    end: "2025-10-31",
    inventory: 200,
    status: "进行中",
    statusCode: "running",
    channel: "全渠道",
    updatedAt: "2025-10-14 10:12",
  },
  {
    id: "SALE-3002",
    product: "星河智慧家庭套装",
    type: "presale",
    price: "定金 ¥ 199 / 尾款 ¥ 11800",
    start: "2025-10-25",
    end: "2025-11-05",
    inventory: 500,
    status: "待开始",
    statusCode: "scheduled",
    channel: "线上预售",
    updatedAt: "2025-10-13 19:41",
  },
  {
    id: "SALE-3003",
    product: "星河空气炸锅",
    type: "group",
    price: "拼团价 ¥ 399",
    start: "2025-10-15",
    end: "2025-10-25",
    inventory: 1000,
    status: "进行中",
    statusCode: "active",
    channel: "拼团",
    updatedAt: "2025-10-12 08:22",
  },
];

function findSaleById(saleId) {
  return salesData.find((item) => item.id === saleId);
}

function refreshSalesView() {
  if (state.route === "product" && state.tabs.product === "product-sales") {
    renderProduct();
  } else {
    renderSalesTable();
  }
}

function formatSalesTypeLabel(type) {
  return type === "normal" ? "普通销售" : type === "presale" ? "预售" : "团购";
}

function openSalesCreateForm() {
  const productOptions = productData
    .filter((item) => item.status === "approved")
    .map((item) => `<option value="${item.name}">${item.name}</option>`)
    .join("");
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">销售计划</div>
      <div class="form-grid">
        <label class="form-field">
          <span>商品 *</span>
          <select id="sales-form-product">${productOptions}</select>
        </label>
        <label class="form-field">
          <span>销售类型 *</span>
          <select id="sales-form-type">
            <option value="normal">普通销售</option>
            <option value="presale">预售</option>
            <option value="group">团购</option>
          </select>
        </label>
        <label class="form-field">
          <span>价格描述 *</span>
          <input type="text" id="sales-form-price" placeholder="例如 ¥ 5999 或 定金/尾款" />
        </label>
        <label class="form-field">
          <span>起始日期 *</span>
          <input type="date" id="sales-form-start" />
        </label>
        <label class="form-field">
          <span>结束日期 *</span>
          <input type="date" id="sales-form-end" />
        </label>
        <label class="form-field">
          <span>库存/名额 *</span>
          <input type="number" id="sales-form-inventory" min="0" step="1" />
        </label>
        <label class="form-field">
          <span>销售渠道</span>
          <input type="text" id="sales-form-channel" placeholder="例如 线上/线下" />
        </label>
      </div>
    </div>
  `;
  openModal({
    title: "创建销售计划",
    body,
    confirmText: "创建并提交",
    onConfirm: () => {
      const product = document.getElementById("sales-form-product")?.value;
      const type = document.getElementById("sales-form-type")?.value;
      const price = document.getElementById("sales-form-price")?.value.trim();
      const start = document.getElementById("sales-form-start")?.value;
      const end = document.getElementById("sales-form-end")?.value;
      const inventoryValue = Number(
        document.getElementById("sales-form-inventory")?.value
      );
      if (
        !product ||
        !type ||
        !price ||
        !start ||
        !end ||
        Number.isNaN(inventoryValue)
      ) {
        showToast("请补齐销售计划必填信息", "warning");
        return false;
      }
      // 进一步校验：商品状态与时间窗口重叠
      const prodObj = productData.find((p) => p.name === product);
      if (!prodObj || prodObj.status !== "approved") {
        showToast("仅已核准商品可上架", "warning");
        return false;
      }
      const sNew = new Date(start);
      const eNew = new Date(end);
      if (isNaN(sNew) || isNaN(eNew)) {
        showToast("请填写有效的起止日期", "warning");
        return false;
      }
      if (sNew > eNew) {
        showToast("结束日期需晚于开始日期", "warning");
        return false;
      }
      const hasOverlap = salesData.some((item) => {
        if (item.product !== product) return false;
        if (item.statusCode === "offline") return false;
        const s = new Date(item.start);
        const e = new Date(item.end);
        if (isNaN(s) || isNaN(e)) return false;
        return s <= eNew && sNew <= e;
      });
      if (hasOverlap) {
        showToast("销售时间窗口与现有计划重叠", "warning");
        return false;
      }

      salesData.unshift({
        id: `SALE-${Date.now()}`,
        product,
        type,
        price,
        start,
        end,
        inventory: inventoryValue,
        status: "待审核",
        statusCode: "pending",
        channel:
          document.getElementById("sales-form-channel")?.value.trim() ||
          "全渠道",
        updatedAt: formatDateTime(),
      });
      showToast("销售计划已提交审核", "success");
      refreshSalesView();
    },
  });
}

function openSalesEditForm(saleId) {
  const sale = findSaleById(saleId);
  if (!sale) return;
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">编辑销售计划</div>
      <div class="form-grid">
        <label class="form-field">
          <span>价格描述 *</span>
          <input type="text" id="sales-form-price" value="${sale.price}" />
        </label>
        <label class="form-field">
          <span>起始日期 *</span>
          <input type="date" id="sales-form-start" value="${sale.start}" />
        </label>
        <label class="form-field">
          <span>结束日期 *</span>
          <input type="date" id="sales-form-end" value="${sale.end}" />
        </label>
        <label class="form-field">
          <span>库存/名额 *</span>
          <input type="number" id="sales-form-inventory" min="0" step="1" value="${
            sale.inventory
          }" />
        </label>
        <label class="form-field">
          <span>销售渠道</span>
          <input type="text" id="sales-form-channel" value="${
            sale.channel || ""
          }" />
        </label>
      </div>
    </div>
  `;
  openModal({
    title: `编辑销售 · ${sale.product}`,
    body,
    confirmText: "保存",
    onConfirm: () => {
      const price = document.getElementById("sales-form-price")?.value.trim();
      const start = document.getElementById("sales-form-start")?.value;
      const end = document.getElementById("sales-form-end")?.value;
      const inventoryValue = Number(
        document.getElementById("sales-form-inventory")?.value
      );
      if (!price || !start || !end || Number.isNaN(inventoryValue)) {
        showToast("请填写完整的销售信息", "warning");
        return false;
      }
      sale.price = price;
      sale.start = start;
      sale.end = end;
      sale.inventory = inventoryValue;
      sale.channel =
        document.getElementById("sales-form-channel")?.value.trim() ||
        sale.channel;
      sale.updatedAt = formatDateTime();
      showToast(`销售计划 ${sale.id} 已更新`, "success");
      refreshSalesView();
    },
  });
}

function duplicateSalesPlan(saleId) {
  const sale = findSaleById(saleId);
  if (!sale) return;
  const cloneSource = JSON.parse(JSON.stringify(sale));
  const clone = {
    ...cloneSource,
    id: `${sale.id}-COPY-${Date.now()}`,
    status: "草稿",
    statusCode: "draft",
    updatedAt: formatDateTime(),
  };
  salesData.unshift(clone);
  showToast(`已复制销售计划 ${sale.id}，请在草稿中完善信息`, "info");
  refreshSalesView();
}

function openSalesDetail(saleId) {
  const sale = findSaleById(saleId);
  if (!sale) return;
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">销售概览</div>
      <div>商品：${sale.product}</div>
      <div>类型：${formatSalesTypeLabel(sale.type)}</div>
      <div>状态：${sale.status}</div>
      <div>渠道：${sale.channel || "—"}</div>
      <div class="modal-section__minor">最近更新时间：${
        sale.updatedAt || "—"
      }</div>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">计划详情</div>
      <ul class="modal-list">
        <li>• 价格：${sale.price}</li>
        <li>• 销售时间：${sale.start} 至 ${sale.end}</li>
        <li>• 库存/名额：${sale.inventory}</li>
      </ul>
    </div>
  `;
  openModal({
    title: `销售详情 · ${sale.product}`,
    body,
    confirmText: "关闭",
    cancelText: "取消",
    onConfirm: () => {},
  });
}

function openSalesBulkDialog(mode) {
  const prompt = mode === "up" ? "批量上架" : "批量下架";
  openModal({
    title: `${prompt}销售计划`,
    body: `<p>确认${prompt}当前筛选条件下的销售计划吗？系统将更新状态并同步提醒审核团队。</p>`,
    confirmText: "确认",
    onConfirm: () => {
      let count = 0;
      salesData.forEach((sale) => {
        if (mode === "up" && sale.statusCode !== "active") {
          sale.status = "进行中";
          sale.statusCode = "active";
          sale.updatedAt = formatDateTime();
          count += 1;
        } else if (mode === "down" && sale.statusCode !== "offline") {
          sale.status = "已下架";
          sale.statusCode = "offline";
          sale.updatedAt = formatDateTime();
          count += 1;
        }
      });
      showToast(`${prompt}完成，共更新 ${count} 条计划`, "success");
      refreshSalesView();
    },
  });
}

function openSaleDelistDialog(saleId) {
  const sale = findSaleById(saleId);
  if (!sale) return;
  if (sale.statusCode === "offline") {
    showToast("该计划已下架", "info");
    return;
  }
  const today = new Date();
  const todayStr = today.toISOString().slice(0, 10);
  const started = !isNaN(new Date(sale.start)) && today >= new Date(sale.start);
  const isPresale = sale.type === "presale";
  let body = `<p>确认下架该销售计划？系统将把结束日期设置为今天（${todayStr}）。</p>`;
  if (isPresale && started) {
    body += `<p class="modal-section__minor">注意：预售已开始，系统将提示对未支付尾款的订单进行取消并退回定金（模拟）。</p>`;
  }
  openModal({
    title: `下架销售 · ${sale.id}`,
    body,
    confirmText: "确认下架",
    onConfirm: () => {
      sale.end = todayStr;
      sale.status = "已下架";
      sale.statusCode = "offline";
      sale.updatedAt = formatDateTime();
      if (isPresale && started) {
        showToast("已触发未支付尾款订单取消并退回定金（模拟）", "info");
      }
      showToast("已下架", "success");
      refreshSalesView();
    },
  });
}

function openSaleDeleteDialog(saleId) {
  const sale = findSaleById(saleId);
  if (!sale) return;
  const now = new Date();
  const s = new Date(sale.start);
  const e = new Date(sale.end);
  if (!isNaN(s) && !isNaN(e) && now >= s && now <= e) {
    showToast("删除失败：当前处于销售期，请先下架或等待结束", "warning");
    return;
  }
  openModal({
    title: `删除销售 · ${sale.id}`,
    body: `<p>确认删除该销售计划？删除后不可恢复。</p>`,
    confirmText: "删除",
    cancelText: "取消",
    onConfirm: () => {
      const idx = salesData.findIndex((x) => x.id === sale.id);
      if (idx >= 0) salesData.splice(idx, 1);
      showToast("已删除销售计划", "success");
      refreshSalesView();
    },
  });
}

const orderData = [
  {
    id: "ORD-23001",
    customer: "张女士",
    phone: "138****6611",
    address: "上海市浦东新区世纪大道 188 号",
    amount: "¥ 5,999",
    logistics: "顺丰速运",
    payment: "微信支付",
    status: "awaiting_accept",
    createdAt: "2025-10-14 09:45",
    items: [{ name: "星河智能电视 75英寸", qty: 1, price: "¥ 6999" }],
    timeline: ["顾客提交订单", "等待商户确认", "待安排发货"],
  },
  {
    id: "ORD-23002",
    customer: "李先生",
    phone: "137****2212",
    address: "杭州市西湖区文三路 88 号",
    amount: "¥ 12,999",
    logistics: "京东物流",
    payment: "支付宝",
    status: "awaiting_ship",
    createdAt: "2025-10-13 21:12",
    items: [{ name: "星河智慧家庭套装", qty: 1, price: "¥ 12999" }],
    timeline: ["订单已确认", "正在备货", "待打印发货单"],
  },
  {
    id: "ORD-23003",
    customer: "王女士",
    phone: "186****8899",
    address: "苏州市工业园区星湖街 68 号",
    amount: "¥ 399",
    logistics: "顺丰速运",
    payment: "微信支付",
    status: "shipped",
    createdAt: "2025-10-12 13:44",
    items: [{ name: "星河空气炸锅", qty: 1, price: "¥ 499" }],
    timeline: ["订单已发货", "包裹在途", "预计两日达"],
  },
  {
    id: "ORD-23004",
    customer: "赵先生",
    phone: "139****3311",
    address: "南京市建邺区江东中路 88 号",
    amount: "¥ 5,499",
    logistics: "顺丰速运",
    payment: "微信支付",
    status: "finished",
    createdAt: "2025-10-10 10:30",
    items: [{ name: "星河智能洗衣机", qty: 1, price: "¥ 5499" }],
    timeline: ["顾客已签收", "售后在 7 日内可发起", "已好评"],
  },
];

function findOrderById(orderId) {
  return orderData.find((item) => item.id === orderId);
}

// 示例数据说明：
// type: 0-退货（含退款） 1-换货 2-寄修 3-上门维修
// status: 0-待审核 1-待验收 2-待上门 3-已取消 4-已验收 5-维修中 6-已完成
// 
// API对应关系：
// - 列表查询: GET /shops/{shopId}/aftersales
// - 详情查看: GET /shops/{shopId}/aftersales/{id}
// - 审核(通过/驳回): PUT /shops/{shopId}/aftersales/{id}/review
// - 验收(通过/不通过): PUT /shops/{shopId}/aftersales/{id}/inspection
// - 完成售后: PUT /shops/{shopId}/aftersales/{id}/complete
// - 取消售后: PUT /shops/{shopId}/aftersales/{id}/cancel
// - 登记备注: POST /shops/{shopId}/aftersales/{id}/logs

const aftersaleData = [
  // ========== 状态0: 待审核 ==========
  // 场景：顾客刚提交售后申请，等待商户审核
  // 操作按钮：审核通过、驳回申请
  // API: PUT /review (approved=true/false)
  {
    id: "AFS-1001",
    customer: "陈女士",
    phone: "138****3331",
    type: 0, // 退货（含退款）
    status: 0, // 待审核
    createdAt: "2025-10-14 15:40",
    orderId: "ORD-23001",
    reason: "商品与描述不符，申请退货退款",
    attachments: 3,
    timeline: ["2025-10-14 15:40 · 顾客提交退货申请", "等待商户审核"],
    serviceOrder: null, // 审核前无服务单
    package: null, // 审核前无运单
  },
  {
    id: "AFS-1002",
    customer: "张先生",
    phone: "139****5566",
    type: 3, // 上门维修
    status: 0, // 待审核
    createdAt: "2025-10-14 10:20",
    orderId: "ORD-23010",
    reason: "电视无法开机，申请上门维修",
    attachments: 2,
    timeline: ["2025-10-14 10:20 · 顾客提交维修申请", "等待商户审核"],
    serviceOrder: null,
    package: null,
  },

  // ========== 状态1: 待验收 ==========
  // 场景：商户审核通过(退货/换货/寄修)，产生运单，顾客已寄回，等待商户验收
  // 操作按钮：验收通过、验收不通过、登记备注
  // API: PUT /inspection (passed=true/false)
  // 「按运单收货」功能：输入运单号 SF1234567890 可查到此记录
  {
    id: "AFS-1003",
    customer: "李先生",
    phone: "186****8831",
    type: 0, // 退货
    status: 1, // 待验收
    createdAt: "2025-10-13 11:05",
    orderId: "ORD-23003",
    reason: "包装破损，商品有划痕",
    attachments: 2,
    timeline: [
      "2025-10-13 11:05 · 顾客提交退货申请",
      "2025-10-13 14:30 · 商户审核通过，生成退货运单",
      "2025-10-13 18:00 · 顾客已寄出，等待商户验收",
    ],
    serviceOrder: null,
    package: {
      id: "PKG-001",
      type: 1, // 顾客寄商家
      waybillNo: "SF1234567890",
      logistics: "顺丰速运",
    },
  },
  {
    id: "AFS-1004",
    customer: "周女士",
    phone: "139****7788",
    type: 1, // 换货
    status: 1, // 待验收
    createdAt: "2025-10-12 09:12",
    orderId: "ORD-23004",
    reason: "收到颜色错误，申请换货",
    attachments: 1,
    timeline: [
      "2025-10-12 09:12 · 顾客提交换货申请",
      "2025-10-12 11:00 · 商户审核通过，生成换货运单",
      "2025-10-13 10:00 · 顾客已寄出旧商品",
    ],
    serviceOrder: null,
    package: {
      id: "PKG-002",
      type: 1,
      waybillNo: "JD9876543210",
      logistics: "京东物流",
    },
  },

  // ========== 状态2: 待上门 ==========
  // 场景：商户审核通过(上门维修)，产生服务单，等待工程师上门验收
  // 操作按钮：验收通过、验收不通过、查看服务单
  // API: PUT /inspection (passed=true/false)
  {
    id: "AFS-1005",
    customer: "赵先生",
    phone: "137****2233",
    type: 3, // 上门维修
    status: 2, // 待上门
    createdAt: "2025-10-11 16:30",
    orderId: "ORD-23005",
    reason: "空调不制冷，申请上门维修",
    attachments: 1,
    timeline: [
      "2025-10-11 16:30 · 顾客提交维修申请",
      "2025-10-11 17:00 · 商户审核通过，生成服务单",
      "2025-10-12 09:00 · 工程师已预约上门时间：10-13 14:00",
    ],
    serviceOrder: {
      id: "SV-REP-20251011-01",
      type: "上门维修",
      assigned: "工程师 刘凯",
      status: "待上门",
      appointmentTime: "2025-10-13 14:00",
      steps: [
        "2025-10-11 17:00 · 系统生成服务单",
        "2025-10-12 09:00 · 工程师预约上门时间",
      ],
    },
    package: null, // 上门维修无运单
  },

  // ========== 状态4: 已验收 ==========
  // 场景：商户验收通过(退货/换货/寄修)，等待完成售后处理
  // 操作按钮：完成售后、取消售后、登记备注
  // API: PUT /complete 或 PUT /cancel
  {
    id: "AFS-1006",
    customer: "孙女士",
    phone: "135****4455",
    type: 0, // 退货
    status: 4, // 已验收
    createdAt: "2025-10-10 14:00",
    orderId: "ORD-23006",
    reason: "商品质量问题，申请退货",
    attachments: 2,
    timeline: [
      "2025-10-10 14:00 · 顾客提交退货申请",
      "2025-10-10 15:30 · 商户审核通过",
      "2025-10-11 12:00 · 顾客已寄出",
      "2025-10-12 10:00 · 商户验收通过，等待退款",
    ],
    serviceOrder: null,
    package: {
      id: "PKG-003",
      type: 1,
      waybillNo: "YT1122334455",
      logistics: "圆通速递",
    },
  },

  // ========== 状态5: 维修中 ==========
  // 场景：工程师上门验收通过，正在进行维修
  // 操作按钮：完成维修、取消维修、查看服务单
  // API: PUT /complete 或 PUT /cancel
  {
    id: "AFS-1007",
    customer: "钱先生",
    phone: "136****6677",
    type: 3, // 上门维修
    status: 5, // 维修中
    createdAt: "2025-10-09 11:00",
    orderId: "ORD-23007",
    reason: "洗衣机漏水，申请维修",
    attachments: 3,
    timeline: [
      "2025-10-09 11:00 · 顾客提交维修申请",
      "2025-10-09 14:00 · 商户审核通过",
      "2025-10-10 10:00 · 工程师上门验收通过",
      "2025-10-10 10:30 · 开始维修",
    ],
    serviceOrder: {
      id: "SV-REP-20251009-02",
      type: "上门维修",
      assigned: "工程师 王强",
      status: "维修中",
      steps: [
        "2025-10-09 14:00 · 系统生成服务单",
        "2025-10-10 10:00 · 工程师上门验收",
        "2025-10-10 10:30 · 开始更换排水管",
      ],
    },
    package: null,
  },

  // ========== 状态6: 已完成 ==========
  // 场景：售后流程已全部完成
  // 操作按钮：查看服务单（只读）
  {
    id: "AFS-1008",
    customer: "王先生",
    phone: "135****9922",
    type: 2, // 寄修
    status: 6, // 已完成
    createdAt: "2025-10-05 18:00",
    orderId: "ORD-23008",
    reason: "屏幕花屏，申请寄修",
    attachments: 4,
    timeline: [
      "2025-10-05 18:00 · 顾客提交寄修申请",
      "2025-10-05 19:00 · 商户审核通过",
      "2025-10-06 12:00 · 顾客已寄出",
      "2025-10-07 10:00 · 商户验收通过",
      "2025-10-08 16:00 · 维修完成，已寄回顾客",
      "2025-10-09 14:00 · 顾客确认收货，售后完成",
    ],
    serviceOrder: {
      id: "SV-REP-20251005-03",
      type: "寄修服务",
      assigned: "维修中心",
      status: "已完成",
      steps: [
        "2025-10-07 10:00 · 收到商品，开始检测",
        "2025-10-08 14:00 · 更换显示排线",
        "2025-10-08 16:00 · 维修完成，已寄回",
      ],
      report: "更换显示排线并进行屏幕校准，测试通过。",
    },
    package: {
      id: "PKG-004",
      type: 1,
      waybillNo: "SF9988776655",
      logistics: "顺丰速运",
    },
  },

  // ========== 状态3: 已取消 ==========
  // 场景：售后被取消（驳回/验收不通过/主动取消）
  // 操作按钮：查看服务单（只读）
  {
    id: "AFS-1009",
    customer: "吴女士",
    phone: "138****1122",
    type: 0, // 退货
    status: 3, // 已取消
    createdAt: "2025-10-08 09:00",
    orderId: "ORD-23009",
    reason: "不想要了，申请退货",
    cancelReason: "商品已拆封使用，不符合退货条件",
    attachments: 1,
    timeline: [
      "2025-10-08 09:00 · 顾客提交退货申请",
      "2025-10-08 11:00 · 商户驳回：商品已拆封使用，不符合退货条件",
    ],
    serviceOrder: null,
    package: null,
  },
];

const AFTERSALE_TYPE_OPTIONS = [
  { value: 0, label: "退货（含退款）" },
  { value: 1, label: "换货" },
  { value: 2, label: "寄修" },
  { value: 3, label: "上门维修" },
];

const AFTERSALE_TYPE_LABELS = {
  0: "退货（含退款）",
  1: "换货",
  2: "寄修",
  3: "上门维修",
  // 兼容旧数据
  "退款": "退货（含退款）",
  "退货": "退货（含退款）",
  "换货": "换货",
  "维修": "上门维修",
};

function findAftersaleById(id) {
  return aftersaleData.find((item) => item.id === id);
}

function appendAftersaleTimeline(record, message) {
  const entry = `${formatDateTime()} · ${message}`;
  record.timeline = [...(record.timeline || []), entry];
}

function getNextAftersaleStatusOptions(status) {
  switch (status) {
    case "pending_review":
      return [
        { value: "in_progress", label: "审核通过，进入处理" },
        { value: "finished", label: "审核拒绝/直接关闭" },
      ];
    case "in_progress":
      return [
        { value: "waiting_receipt", label: "等待顾客寄回/确认" },
        { value: "finished", label: "完成售后" },
      ];
    case "waiting_receipt":
      return [{ value: "finished", label: "确认收货，完成售后" }];
    default:
      return [];
  }
}

function ensureAftersaleServiceOrder(record) {
  if (record.type === "退款") {
    return null;
  }
  if (!record.serviceOrder) {
    const baseId =
      record.type === "维修"
        ? "SV-REP"
        : record.type === "换货"
        ? "SV-EXC"
        : "SV-RET";
    record.serviceOrder = {
      id: `${baseId}-${Date.now()}`,
      type:
        record.type === "维修"
          ? "维修服务"
          : record.type === "换货"
          ? "换货补发"
          : "退货物流",
      assigned: "售后专员 待分配",
      status: "处理中",
      logistics: null,
      steps: [`${formatDateTime()} · 系统已生成服务单，等待专员接单`],
      report: null,
    };
  }
  return record.serviceOrder;
}

const paymentData = [
  {
    id: "PAY-89001",
    order: "ORD-23001",
    time: "2025-10-14 09:41",
    amount: "¥ 5,999",
    channel: "微信支付",
    share: "已分账",
  },
  {
    id: "PAY-89002",
    order: "ORD-23002",
    time: "2025-10-13 21:12",
    amount: "¥ 12,999",
    channel: "支付宝",
    share: "待分账",
  },
  {
    id: "PAY-89003",
    order: "ORD-23003",
    time: "2025-10-12 13:44",
    amount: "¥ 399",
    channel: "微信支付",
    share: "已分账",
  },
];

function findPaymentById(id) {
  return paymentData.find((item) => item.id === id);
}

const refundData = [
  {
    id: "REF-99001",
    paymentId: "PAY-89002",
    time: "2025-10-14 16:20",
    amount: "¥ 12,999",
    share: "待退分账",
  },
  {
    id: "REF-99000",
    paymentId: "PAY-88999",
    time: "2025-10-12 08:30",
    amount: "¥ 399",
    share: "已完成",
  },
];

function findRefundById(id) {
  return refundData.find((item) => item.id === id);
}

const serviceData = [
  {
    id: "SRV-1001",
    name: "电视上门安装标准版",
    type: "上门安装",
    regions: ["长三角", "珠三角"],
    products: ["星河智能电视 75英寸"],
    price: "¥ 199",
    status: "active",
    description: "含墙体勘察、挂架安装、调试及清洁",
    category: "安装服务",
    contract: "CTR-88001",
    contact: "盛唐服务商 · 王主管",
    audits: [
      { time: "2025-10-12", result: "已通过" },
      { time: "2025-10-10", result: "提交审核" },
    ],
    updatedAt: "2025-10-12 09:10",
  },
  {
    id: "SRV-1002",
    name: "空调深度保养",
    type: "上门维修",
    regions: ["上海", "苏州"],
    products: ["星河空调 X 系列"],
    price: "¥ 299",
    status: "pending",
    description: "包含清洗、消毒、试运行",
    category: "保养服务",
    contract: "CTR-88002",
    contact: "广联上门服务 · 李经理",
    audits: [{ time: "2025-10-14", result: "等待平台审核" }],
    updatedAt: "2025-10-14 08:50",
  },
];

function findServiceById(serviceId) {
  return serviceData.find((item) => item.id === serviceId);
}

function refreshServiceTable() {
  if (state.route === "service") {
    renderServices();
  } else {
    renderServices();
  }
}

const providerData = [
  {
    id: "PRV-001",
    name: "盛唐服务商",
    types: "安装 / 维修",
    region: "上海、杭州",
    contact: "王主管 138****8890",
    status: "合作中",
    rating: "A",
    services: ["电视上门安装标准版", "空调深度保养"],
    joinedAt: "2023-08-01",
    recentCases: [
      "2025-10-10 完成 58 单安装服务",
      "2025-10-12 完成 12 单维修服务",
    ],
    updatedAt: "2025-10-12 18:00",
  },
  {
    id: "PRV-002",
    name: "广联上门服务",
    types: "安装",
    region: "广州、深圳",
    contact: "李经理 136****8822",
    status: "待考察",
    rating: "B",
    services: ["智能家居调试"],
    joinedAt: "2024-04-18",
    recentCases: [
      "2025-09-28 完成 8 单试运行调试",
      "2025-10-05 完成 5 单开通服务",
    ],
    updatedAt: "2025-10-05 12:20",
  },
];

const contractData = [
  {
    id: "CTR-88001",
    provider: "盛唐服务商",
    service: "电视上门安装",
    region: "上海、杭州",
    effectDate: "2025-09-01",
    expireDate: "2026-08-31",
    status: "active",
    statusCode: "active",
    scope: "安装服务，标准响应48小时内上门",
    terms: [
      "平台与服务商按 7:3 进行收入结算",
      "服务商需提供实名认证工程师资料",
      "出现服务纠纷须在 24 小时内反馈",
    ],
    timeline: [
      { time: "2025-08-25", event: "双方签署意向书" },
      { time: "2025-08-28", event: "平台审核合同条款" },
      { time: "2025-09-01", event: "合同正式生效" },
    ],
    updatedAt: "2025-09-01 09:00",
  },
  {
    id: "CTR-88002",
    provider: "广联上门服务",
    service: "智慧家居调试",
    region: "广州、深圳",
    effectDate: "2025-10-01",
    expireDate: "2026-09-30",
    status: "pending",
    statusCode: "pending",
    scope: "智能家居设备调试与验收",
    terms: [
      "首次签约需通过现场考察",
      "平台提供培训资料并要求通过考核",
      "违约需提前 30 日告知",
    ],
    timeline: [
      { time: "2025-09-25", event: "服务商提交合同申请" },
      { time: "2025-09-27", event: "平台初审通过，等待考察" },
    ],
    updatedAt: "2025-09-27 11:30",
  },
];

function findProviderById(id) {
  return providerData.find((item) => item.id === id);
}

function findContractById(id) {
  return contractData.find((item) => item.id === id);
}

function refreshContractTable() {
  if (state.route === "partner") {
    renderContractTable();
  }
}

const CONTRACT_STATUS_META = {
  pending: { label: "待确认", tone: "warning" },
  active: { label: "生效中", tone: "success" },
  paused: { label: "已暂停", tone: "info" },
  cancelled: { label: "已终止", tone: "danger" },
};

function appendContractTimeline(contract, message) {
  contract.timeline = [
    ...(contract.timeline || []),
    { time: formatDateTime(), event: message },
  ];
}

const promoData = [
  {
    id: "ACT-2001",
    name: "双十一电视直降",
    type: "限时折扣",
    rule: "满 1 件 8 折",
    start: "2025-11-01",
    end: "2025-11-12",
    status: "进行中",
    statusCode: "active",
    channel: "全站线上",
    description: "大件家电双十一钜惠，限量 500 套。",
    budget: "市场预算 200,000 元",
    products: ["SKU-88001"],
    timeline: [
      { time: "2025-10-15", event: "创建促销活动" },
      { time: "2025-10-20", event: "平台审核通过" },
      { time: "2025-11-01", event: "活动正式上线" },
    ],
    createdAt: "2025-10-15 10:00",
    updatedAt: "2025-11-01 00:00",
  },
  {
    id: "ACT-2002",
    name: "会员专享券",
    type: "满减券",
    rule: "满 3000 减 300",
    start: "2025-10-20",
    end: "2025-11-20",
    status: "草稿",
    statusCode: "draft",
    channel: "会员中心",
    description: "针对会员群体的秋季家电优惠券，等待平台审批。",
    budget: "券预算 50,000 元",
    products: ["SKU-88003", "SKU-88004"],
    timeline: [{ time: "2025-10-12", event: "活动草案提交待审核" }],
    createdAt: "2025-10-12 09:30",
    updatedAt: "2025-10-12 09:30",
  },
];

const groupData = [
  {
    id: "GRP-1001",
    name: "空气炸锅拼团",
    membersRequired: 3,
    start: "2025-10-15",
    end: "2025-10-25",
    price: "¥ 399",
    status: "进行中",
    statusCode: "active",
    description: "拼团下单成功后 24 小时内发货。",
    successCount: 128,
    timeline: [
      { time: "2025-10-10", event: "提交拼团活动审核" },
      { time: "2025-10-12", event: "活动上线" },
    ],
    products: ["SKU-88003"],
    createdAt: "2025-10-10 08:00",
    updatedAt: "2025-10-15 00:00",
  },
  {
    id: "GRP-1002",
    name: "洗衣机开仓价",
    membersRequired: 5,
    start: "2025-11-01",
    end: "2025-11-15",
    price: "¥ 2,999",
    status: "待开始",
    statusCode: "scheduled",
    description: "预售拼团，满 5 人成团，未成团自动退款。",
    successCount: 0,
    timeline: [{ time: "2025-10-18", event: "活动草案提交" }],
    products: ["SKU-88004"],
    createdAt: "2025-10-18 15:20",
    updatedAt: "2025-10-18 15:20",
  },
];

const assignActivities = [
  {
    id: "ACT-2001",
    name: "双十一电视直降",
    type: "促销",
    window: "11.01-11.12",
  },
  { id: "GRP-1001", name: "空气炸锅拼团", type: "团购", window: "10.15-10.25" },
];

const assignProducts = [
  { id: "SKU-88001", name: "星河智能电视 75英寸" },
  { id: "SKU-88003", name: "星河空气炸锅" },
  { id: "SKU-88005", name: "星河蒸汽拖把" },
];

const PROMO_STATUS_META = {
  draft: { label: "草稿", tone: "info" },
  pending: { label: "待审核", tone: "warning" },
  running: { label: "进行中", tone: "success" },
  finished: { label: "已结束", tone: "danger" },
};

const GROUP_STATUS_META = {
  scheduled: { label: "待开始", tone: "warning" },
  active: { label: "进行中", tone: "success" },
  finished: { label: "已结束", tone: "info" },
  cancelled: { label: "已取消", tone: "danger" },
};

const activityAssignments = {
  "ACT-2001": ["SKU-88001"],
  "GRP-1001": ["SKU-88003"],
};

const els = {};

function setPromoStatus(promo, statusCode) {
  promo.statusCode = statusCode;
  promo.status = PROMO_STATUS_META[statusCode]?.label || statusCode;
}

function setGroupStatus(group, statusCode) {
  group.statusCode = statusCode;
  group.status = GROUP_STATUS_META[statusCode]?.label || statusCode;
}

function normalizePromoStatusCode(status) {
  if (!status) return "draft";
  const map = {
    草稿: "draft",
    draft: "draft",
    待审核: "pending",
    pending: "pending",
    审核中: "pending",
    待开始: "pending",
    进行中: "running",
    running: "running",
    已结束: "finished",
    finished: "finished",
    已终止: "finished",
  };
  return map[status] || status;
}

function normalizeGroupStatusCode(status) {
  if (!status) return "scheduled";
  const map = {
    待开始: "scheduled",
    scheduled: "scheduled",
    进行中: "active",
    active: "active",
    已结束: "finished",
    finished: "finished",
    已取消: "cancelled",
    cancelled: "cancelled",
  };
  return map[status] || status;
}

promoData.forEach((promo) => {
  const code = normalizePromoStatusCode(promo.statusCode || promo.status);
  setPromoStatus(promo, code);
});

groupData.forEach((group) => {
  const code = normalizeGroupStatusCode(group.statusCode || group.status);
  setGroupStatus(group, code);
});

function init() {
  cacheElements();
  bindNavigation();
  bindTabSwitch();
  bindFilters();
  bindGlobalActions();
  renderRoute(state.route);
  renderBreadcrumb();
  renderTopbarStats();
}

function cacheElements() {
  els.sections = document.querySelectorAll("[data-section]");
  els.navItems = document.querySelectorAll(".nav-item[data-route]");
  els.breadcrumb = document.getElementById("breadcrumb-current");
  els.toastContainer = document.getElementById("toast-container");
  els.modal = document.getElementById("modal");
  els.modalTitle = document.getElementById("modal-title");
  els.modalBody = document.getElementById("modal-body");
  els.modalConfirm = document.getElementById("modal-confirm");
  els.modalCancel = document.getElementById("modal-cancel");

  els.accountTimeline = document.getElementById("account-timeline");
  els.staffTable = document.getElementById("staff-table");
  els.staffEmpty = document.getElementById("staff-empty");
  els.staffSearch = document.getElementById("staff-search");
  els.staffStatusFilter = document.getElementById("staff-status-filter");
  els.staffRoleFilter = document.getElementById("staff-role-filter");

  els.productSearch = document.getElementById("product-search");
  els.productStatusFilter = document.getElementById("product-status-filter");
  els.productTypeFilter = document.getElementById("product-type-filter");
  els.productTable = document.getElementById("product-table");
  els.productEmpty = document.getElementById("product-empty");
  els.salesTabs = document.getElementById("sales-type-tabs");
  els.salesTable = document.getElementById("sales-table");
  els.salesEmpty = document.getElementById("sales-empty");
  els.salesSearch = document.getElementById("sales-search");
  els.salesStart = document.getElementById("sales-start");
  els.salesEnd = document.getElementById("sales-end");
  els.salesStatus = document.getElementById("sales-status");

  els.orderDate = document.getElementById("order-date");
  els.orderRegion = document.getElementById("order-region");
  els.orderPhone = document.getElementById("order-phone");

  els.orderStatusStrip = document.getElementById("order-status-strip");
  els.orderSearch = document.getElementById("order-search");
  els.orderStatus = document.getElementById("order-status-filter");
  els.orderTable = document.getElementById("order-table");
  els.orderEmpty = document.getElementById("order-empty");

  els.aftersaleStatus = document.getElementById("aftersale-status");
  els.aftersaleSearch = document.getElementById("aftersale-search");
  els.aftersaleType = document.getElementById("aftersale-type");
  els.aftersalePhone = document.getElementById("aftersale-phone");
  els.aftersaleTable = document.getElementById("aftersale-table");
  els.aftersaleEmpty = document.getElementById("aftersale-empty");
  els.paymentAmount = document.getElementById("payment-amount");
  els.aftersaleWaybill = document.getElementById("aftersale-waybill");

  els.paymentDate = document.getElementById("payment-date");
  els.paymentChannel = document.getElementById("payment-channel");
  els.paymentNo = document.getElementById("payment-no");
  els.paymentTable = document.getElementById("payment-table");
  els.paymentEmpty = document.getElementById("payment-empty");

  els.refundAmount = document.getElementById("refund-amount");
  els.refundDate = document.getElementById("refund-date");
  els.refundNo = document.getElementById("refund-no");
  els.refundTable = document.getElementById("refund-table");
  els.refundEmpty = document.getElementById("refund-empty");

  els.serviceTable = document.getElementById("service-table");
  els.serviceEmpty = document.getElementById("service-empty");

  els.serviceSearch = document.getElementById("service-search");
  els.serviceTypeFilter = document.getElementById("service-type");
  els.serviceProductFilter = document.getElementById("service-product");
  els.serviceStatusFilter = document.getElementById("service-status");
  els.serviceRegionFilter = document.getElementById("service-region");

  els.providerTable = document.getElementById("provider-table");
  els.providerEmpty = document.getElementById("provider-empty");
  els.providerSearch = document.getElementById("provider-search");
  els.providerType = document.getElementById("provider-type");
  els.providerRegion = document.getElementById("provider-region");
  els.contractTable = document.getElementById("contract-table");
  els.contractEmpty = document.getElementById("contract-empty");

  els.promoTable = document.getElementById("promo-table");
  els.promoEmpty = document.getElementById("promo-empty");
  els.promoSearch = document.getElementById("promo-search");
  els.promoStatus = document.getElementById("promo-status");
  els.groupTable = document.getElementById("group-table");
  els.promoStart = document.getElementById("promo-start");
  els.promoEnd = document.getElementById("promo-end");
  els.promoProduct = document.getElementById("promo-product");
  els.groupSearch = document.getElementById("group-search");
  els.groupStart = document.getElementById("group-start");
  els.groupEnd = document.getElementById("group-end");
  els.assignActivityList = document.getElementById("assign-activity-list");
  els.assignProductList = document.getElementById("assign-product-list");

  els.groupEmpty = document.getElementById("group-empty");
}

function bindNavigation() {
  els.navItems.forEach((item) => {
    item.addEventListener("click", () => {
      const route = item.dataset.route;
      if (route) {
        setRoute(route);
      }
    });
  });
}

function bindTabSwitch() {
  document.querySelectorAll("[data-tabs]").forEach((group) => {
    group.addEventListener("click", (event) => {
      const btn = event.target.closest(".tab");
      if (!btn) return;
      const target = btn.dataset.tabTarget;
      const namespace = group.dataset.tabs;
      if (!target || !namespace) return;
      state.tabs[namespace] = target;
      activateTab(namespace, target);
      renderRoute(state.route);
    });
  });
}

function bindFilters() {
  if (els.staffSearch)
    els.staffSearch.addEventListener("input", (e) => {
      state.staffFilters.keyword = e.target.value.trim();
      renderStaffTable();
    });
  if (els.staffStatusFilter)
    els.staffStatusFilter.addEventListener("change", (e) => {
      state.staffFilters.status = e.target.value;
      renderStaffTable();
    });
  if (els.staffRoleFilter)
    els.staffRoleFilter.addEventListener("change", (e) => {
      state.staffFilters.role = e.target.value;
      renderStaffTable();
    });

  if (els.productSearch)
    els.productSearch.addEventListener("input", (e) => {
      state.productFilters.keyword = e.target.value.trim();
      renderProductItems();
    });
  if (els.productStatusFilter)
    els.productStatusFilter.addEventListener("change", (e) => {
      state.productFilters.status = e.target.value;
      renderProductItems();
    });
  if (els.productTypeFilter)
    els.productTypeFilter.addEventListener("change", (e) => {
      state.productFilters.type = e.target.value;
      renderProductItems();
    });

  if (els.orderDate)
    els.orderDate.addEventListener("change", (e) => {
      state.orderFilters.date = e.target.value;
      renderOrders();
    });
  if (els.orderRegion)
    els.orderRegion.addEventListener("input", (e) => {
      state.orderFilters.region = e.target.value.trim();
      renderOrders();
    });
  if (els.orderPhone)
    els.orderPhone.addEventListener("input", (e) => {
      state.orderFilters.phone = e.target.value.trim();
      renderOrders();
    });
  if (els.orderSearch)
    els.orderSearch.addEventListener("input", (e) => {
      state.orderFilters.keyword = e.target.value.trim();
      renderOrders();
    });
  if (els.orderStatus)
    els.orderStatus.addEventListener("change", (e) => {
      state.orderFilters.status = e.target.value;
      renderOrders();
    });

  if (els.salesSearch)
    els.salesSearch.addEventListener("input", (e) => {
      state.salesFilters.keyword = e.target.value.trim();
      renderSalesTable();
    });
  if (els.salesStart)
    els.salesStart.addEventListener("change", (e) => {
      state.salesFilters.start = e.target.value;
      renderSalesTable();
    });
  if (els.salesEnd)
    els.salesEnd.addEventListener("change", (e) => {
      state.salesFilters.end = e.target.value;
      renderSalesTable();
    });
  if (els.salesStatus)
    els.salesStatus.addEventListener("change", (e) => {
      state.salesFilters.status = e.target.value;
      renderSalesTable();
    });

  if (els.aftersaleSearch)
    els.aftersaleSearch.addEventListener("input", (e) => {
      state.aftersaleFilters.keyword = e.target.value.trim();
      renderAftersales();
    });
  if (els.aftersaleType)
    els.aftersaleType.addEventListener("change", (e) => {
      state.aftersaleFilters.type = e.target.value;
      renderAftersales();
    });
  if (els.aftersaleWaybill)
    els.aftersaleWaybill.addEventListener("input", (e) => {
      state.aftersaleFilters.waybill = e.target.value.trim();
      renderAftersales();
    });
  if (els.aftersalePhone)
    els.aftersalePhone.addEventListener("input", (e) => {
      state.aftersaleFilters.phone = e.target.value.trim();
      renderAftersales();
    });

  if (els.paymentDate)
    els.paymentDate.addEventListener("change", (e) => {
      state.paymentFilters.date = e.target.value;
      renderFinance();
    });
  if (els.paymentAmount)
    els.paymentAmount.addEventListener("input", (e) => {
      state.paymentFilters.amount = e.target.value.trim();
      renderFinance();
    });
  if (els.paymentChannel)
    els.paymentChannel.addEventListener("change", (e) => {
      state.paymentFilters.channel = e.target.value;
      renderFinance();
    });
  if (els.refundDate)
    els.refundDate.addEventListener("change", (e) => {
      state.refundFilters.date = e.target.value;
      renderFinance();
    });
  if (els.refundAmount)
    els.refundAmount.addEventListener("input", (e) => {
      state.refundFilters.amount = e.target.value.trim();
      renderFinance();
    });
  if (els.paymentNo)
    els.paymentNo.addEventListener("input", (e) => {
      state.paymentFilters.keyword = e.target.value.trim();
      renderFinance();
    });
  if (els.refundNo)
    els.refundNo.addEventListener("input", (e) => {
      state.refundFilters.keyword = e.target.value.trim();
      renderFinance();
    });

  if (els.providerSearch)
    els.providerSearch.addEventListener("input", (e) => {
      state.providerKeyword = e.target.value.trim();
      renderPartner();
    });
  if (els.providerType)
    els.providerType.addEventListener("change", (e) => {
      state.providerType = e.target.value;
      renderPartner();
    });
  if (els.providerRegion)
    els.providerRegion.addEventListener("input", (e) => {
      state.providerRegion = e.target.value.trim();
      renderPartner();
    });

  if (els.promoSearch)
    els.promoSearch.addEventListener("input", (e) => {
      state.promoKeyword = e.target.value.trim();
      renderActivity();
    });
  if (els.promoStart)
    els.promoStart.addEventListener("change", (e) => {
      state.promoStart = e.target.value;
      renderActivity();
    });
  if (els.promoEnd)
    els.promoEnd.addEventListener("change", (e) => {
      state.promoEnd = e.target.value;
      renderActivity();
    });
  if (els.promoProduct)
    els.promoProduct.addEventListener("input", (e) => {
      state.promoProduct = e.target.value.trim();
      renderActivity();
    });
  if (els.groupSearch)
    els.groupSearch.addEventListener("input", (e) => {
      state.groupKeyword = e.target.value.trim();
      renderActivity();
    });
  if (els.groupStart)
    els.groupStart.addEventListener("change", (e) => {
      state.groupStart = e.target.value;
      renderActivity();
    });
  if (els.groupEnd)
    els.groupEnd.addEventListener("change", (e) => {
      state.groupEnd = e.target.value;
      renderActivity();
    });

  if (els.promoStatus)
    els.promoStatus.addEventListener("change", (e) => {
      state.promoStatus = e.target.value;
      renderActivity();
    });
  // Service filters
  if (els.serviceSearch)
    els.serviceSearch.addEventListener("input", (e) => {
      state.serviceFilters.keyword = e.target.value.trim();
      renderServices();
    });
  if (els.serviceTypeFilter)
    els.serviceTypeFilter.addEventListener("input", (e) => {
      state.serviceFilters.type = e.target.value.trim();
      renderServices();
    });
  if (els.serviceProductFilter)
    els.serviceProductFilter.addEventListener("input", (e) => {
      state.serviceFilters.product = e.target.value.trim();
      renderServices();
    });
  if (els.serviceStatusFilter)
    els.serviceStatusFilter.addEventListener("change", (e) => {
      state.serviceFilters.status = e.target.value;
      renderServices();
    });
  if (els.serviceRegionFilter)
    els.serviceRegionFilter.addEventListener("input", (e) => {
      state.serviceFilters.region = e.target.value.trim();
      renderServices();
    });
}

function bindGlobalActions() {
  document.addEventListener("click", (event) => {
    const actionBtn = event.target.closest("[data-action]");
    if (!actionBtn) return;
    const action = actionBtn.dataset.action;
    const section = actionBtn.closest("[data-section]")?.dataset.section;

    switch (action) {
      case "account-open":
        openAccountOpenWizard();
        break;
      case "account-toggle-admin":
        toggleAdmin();
        break;
      case "account-cancel":
        openAccountCancelDialog();
        break;
      case "save-account":
        openAccountQuickSave();
        break;
      case "view-audit":
        openAccountAuditViewer();
        break;
      case "reset-account":
        openAccountResetDialog();
        break;
      case "submit-account":
        openAccountSubmitDialog();
        break;
      case "edit-quota":
        openQuotaDialog();
        break;
      case "staff-add":
        openStaffCreateModal();
        break;
      case "staff-import":
        openStaffImportGuide();
        break;
      case "staff-reset":
        state.staffFilters = { keyword: "", status: "all", role: "all" };
        if (els.staffSearch) els.staffSearch.value = "";
        if (els.staffStatusFilter) els.staffStatusFilter.value = "all";
        if (els.staffRoleFilter) els.staffRoleFilter.value = "all";
        renderStaffTable();
        break;
      case "download-account-log":
        exportAccountLog();
        break;
      case "product-create":
        openProductCreateForm();
        break;
      case "product-import":
        openProductImportGuide();
        break;
      case "product-reset":
        state.productFilters = { keyword: "", status: "all", type: "all" };
        if (els.productSearch) els.productSearch.value = "";
        if (els.productStatusFilter) els.productStatusFilter.value = "all";
        if (els.productTypeFilter) els.productTypeFilter.value = "all";
        renderProductItems();
        break;
      case "product-detail":
        openProductDetail(actionBtn.dataset.id);
        break;
      case "product-edit":
        openProductEditForm(actionBtn.dataset.id);
        break;
      case "product-change":
        openProductChangeForm(actionBtn.dataset.id);
        break;
      case "sales-create":
        openSalesCreateForm();
        break;
      case "sales-export":
        showToast("正在导出销售报表", "success");
        break;
      case "sales-bulk-up":
        openSalesBulkDialog("up");
        break;
      case "sales-bulk-down":
        openSalesBulkDialog("down");
        break;
      case "sales-edit":
        openSalesEditForm(actionBtn.dataset.id);
        break;
      case "sales-copy":
        duplicateSalesPlan(actionBtn.dataset.id);
        break;
      case "sales-detail":
        openSalesDetail(actionBtn.dataset.id);
        break;
      case "sales-delist":
        openSaleDelistDialog(actionBtn.dataset.id);
        break;
      case "sales-delete":
        openSaleDeleteDialog(actionBtn.dataset.id);
        break;
      case "sales-reset":
        state.salesFilters = { keyword: "", start: "", end: "", status: "all" };
        if (els.salesSearch) els.salesSearch.value = "";
        if (els.salesStart) els.salesStart.value = "";
        if (els.salesEnd) els.salesEnd.value = "";
        if (els.salesStatus) els.salesStatus.value = "all";
        renderSalesTable();
        break;

      case "order-reset":
        state.orderFilters = {
          status: "awaiting_accept",
          keyword: "",
          date: "",
          region: "",
          phone: "",
        };
        if (els.orderSearch) els.orderSearch.value = "";
        if (els.orderStatus) els.orderStatus.value = "all";
        if (els.orderDate) els.orderDate.value = "";
        if (els.orderRegion) els.orderRegion.value = "";
        if (els.orderPhone) els.orderPhone.value = "";
        renderOrders();
        break;
      case "order-accept":
        acceptOrder(actionBtn.dataset.order);
        break;
      case "order-reject":
        openOrderReject(actionBtn.dataset.order);
        break;
      case "order-ship":
        openOrderShipForm(actionBtn.dataset.order);
        break;
      case "order-complete":
        completeOrder(actionBtn.dataset.order);
        break;
      case "order-cancel":
        openOrderCancel(actionBtn.dataset.order);
        break;
      case "order-print-label":
        openOrderPrintLabel(actionBtn.dataset.order);
        break;
      case "order-create-aftersale":
        openOrderAftersaleForm(actionBtn.dataset.order);
        break;
      case "order-view-refund":
        showToast(`订单 ${actionBtn.dataset.order} 的退款正在处理`, "info");
        break;
      case "order-detail":
        openOrderDetail(actionBtn.dataset.order);
        break;
      case "aftersale-reset":
        state.aftersaleFilters = {
          status: "0",
          keyword: "",
          type: "all",
          phone: "",
          waybill: "",
        };
        if (els.aftersaleSearch) els.aftersaleSearch.value = "";
        if (els.aftersaleType) els.aftersaleType.value = "all";
        if (els.aftersalePhone) els.aftersalePhone.value = "";
        if (els.aftersaleWaybill) els.aftersaleWaybill.value = "";
        renderAftersales();
        break;
      case "aftersale-detail":
        openAftersaleDetail(actionBtn.dataset.id);
        break;
      case "aftersale-approve":
        approveAftersale(actionBtn.dataset.id);
        break;
      case "aftersale-reject":
        rejectAftersale(actionBtn.dataset.id);
        break;
      case "aftersale-log":
        openAftersaleLogForm(actionBtn.dataset.id);
        break;
      case "aftersale-confirm":
        confirmAftersaleReceipt(actionBtn.dataset.id);
        break;
      case "aftersale-inspect-pass":
        inspectAftersale(actionBtn.dataset.id, true);
        break;
      case "aftersale-inspect-fail":
        inspectAftersale(actionBtn.dataset.id, false);
        break;
      case "aftersale-complete":
        completeAftersale(actionBtn.dataset.id);
        break;
      case "aftersale-cancel":
        cancelAftersale(actionBtn.dataset.id);
        break;
      case "aftersale-service":
        openAftersaleServiceModal(actionBtn.dataset.id);
        break;
      case "aftersale-receive-waybill":
        openAftersaleReceiveByWaybill();
        break;
      case "finance-export":
        showToast("对账单已生成", "success");
        break;
      case "payment-reset":
        state.paymentFilters = { channel: "all", keyword: "" };
        if (els.paymentChannel) els.paymentChannel.value = "all";
        if (els.paymentNo) els.paymentNo.value = "";
        renderFinance();
        break;
      case "refund-reset":
        state.refundFilters = { keyword: "" };
        if (els.refundNo) els.refundNo.value = "";
        renderFinance();
        break;
      case "payment-detail":
        openPaymentDetailModal(actionBtn.dataset.id);
        break;
      case "refund-detail":
        openRefundDetailModal(actionBtn.dataset.id);
        break;
      case "service-create":
        openServiceCreateForm();
        break;
      case "service-import":
        showToast("请上传服务目录模板", "info");
        break;
      case "service-history":
        openServiceHistoryModal(actionBtn.dataset.id);
        break;
      case "service-detail":
        openServiceDetail(actionBtn.dataset.id);
        break;
      case "service-edit":
        openServiceEditForm(actionBtn.dataset.id);
        break;
      case "service-delete":
        openServiceDeleteDialog(actionBtn.dataset.id);
        break;
      case "service-reset":
        state.serviceFilters = {
          keyword: "",
          type: "",
          product: "",
          status: "all",
          region: "",
        };
        if (els.serviceSearch) els.serviceSearch.value = "";
        if (els.serviceTypeFilter) els.serviceTypeFilter.value = "";
        if (els.serviceProductFilter) els.serviceProductFilter.value = "";
        if (els.serviceStatusFilter) els.serviceStatusFilter.value = "all";
        if (els.serviceRegionFilter) els.serviceRegionFilter.value = "";
        renderServices();
        break;
      case "provider-reset":
        state.providerKeyword = "";
        state.providerType = "all";
        state.providerRegion = "";
        if (els.providerSearch) els.providerSearch.value = "";
        if (els.providerType) els.providerType.value = "all";
        if (els.providerRegion) els.providerRegion.value = "";
        renderPartner();
        break;
      case "provider-invite":
        showToast("邀请邮件已发送给服务商", "success");
        break;
      case "provider-detail":
        openProviderDetail(actionBtn.dataset.id);
        break;
      case "provider-eval":
        openProviderEvaluation(actionBtn.dataset.id);
        break;
      case "contract-create":
        openContractCreateForm();
        break;
      case "contract-export":
        showToast("合同列表导出中", "success");
        break;
      case "contract-template":
        showToast("已下载合同模板", "info");
        break;
      case "contract-detail":
        openContractDetail(actionBtn.dataset.id);
        break;
      case "contract-operate":
        openContractOperate(actionBtn.dataset.id);
        break;
      case "activity-template":
        openActivityTemplateGuide();
        break;
      case "activity-create":
        openActivityCreateForm();
        break;
      case "promo-detail":
        openPromoDetail(actionBtn.dataset.id);
        break;
      case "promo-stop":
        openPromoStopDialog(actionBtn.dataset.id);
        break;
      case "activity-unlink":
        openActivityUnlinkForm(actionBtn.dataset.id);
        break;
      case "group-stop":
        openGroupStopDialog(actionBtn.dataset.id);
        break;

      case "group-detail":
        openGroupDetail(actionBtn.dataset.id);
        break;
      case "group-export":
        showToast("团购数据导出完成", "success");
        break;
      case "promo-reset":
        state.promoKeyword = "";
        state.promoStatus = "all";
        state.promoStart = "";
        state.promoEnd = "";
        state.promoProduct = "";
        if (els.promoSearch) els.promoSearch.value = "";
        if (els.promoStatus) els.promoStatus.value = "all";
        if (els.promoStart) els.promoStart.value = "";
        if (els.promoEnd) els.promoEnd.value = "";
        if (els.promoProduct) els.promoProduct.value = "";
        renderActivity();
        break;
      case "assign-reset":
        state.assign = { activityId: null, productIds: [] };
        renderActivity();
        showToast("已清除已选商品", "info");
        break;
      case "assign-submit":
        if (!state.assign.activityId || !state.assign.productIds.length) {
          showToast("请先选择活动和商品", "warning");
          return;
        }
        activityAssignments[state.assign.activityId] = [
          ...state.assign.productIds,
        ];
        const promoTarget = promoData.find(
          (item) => item.id === state.assign.activityId
        );
        if (promoTarget) {
          promoTarget.products = [...state.assign.productIds];
          promoTarget.updatedAt = formatDateTime();
        }
        const groupTarget = groupData.find(
          (item) => item.id === state.assign.activityId
        );
        if (groupTarget) {
          groupTarget.products = [...state.assign.productIds];
          groupTarget.updatedAt = formatDateTime();
        }
        showToast("指定参与商品已提交", "success");
        state.assign = { activityId: null, productIds: [] };
        renderActivity();
        break;
      default:
        break;
    }
    if (section === "partner" || section === "activity") {
      renderRoute("partner" === section ? "partner" : "activity");
    }
  });

  els.modalCancel.addEventListener("click", closeModal);
  els.modalConfirm.addEventListener("click", () => {
    if (typeof els.modalConfirm._handler === "function") {
      const result = els.modalConfirm._handler();
      if (result === false) {
        return;
      }
    }
    closeModal();
  });
}

function setRoute(route) {
  state.route = route;
  els.sections.forEach((section) => {
    section.classList.toggle("active", section.dataset.section === route);
  });
  els.navItems.forEach((item) => {
    item.classList.toggle("active", item.dataset.route === route);
  });
  renderBreadcrumb();
  renderRoute(route);
}

function activateTab(namespace, target) {
  const container = document.querySelector(`[data-tabs="${namespace}"]`);
  if (!container) return;
  container.querySelectorAll(".tab").forEach((tab) => {
    tab.classList.toggle("active", tab.dataset.tabTarget === target);
  });
  document
    .querySelectorAll(`.tab-panel[data-tab-panel^="${namespace}"]`)
    .forEach((panel) => {
      panel.classList.toggle("active", panel.dataset.tabPanel === target);
    });
}

function renderRoute(route) {
  switch (route) {
    case "account":
      renderAccount();
      break;
    case "product":
      renderProduct();
      break;
    case "order":
      renderOrders();
      break;
    case "aftersale":
      renderAftersales();
      break;
    case "finance":
      renderFinance();
      break;
    case "service":
      renderServices();
      break;
    case "partner":
      renderPartner();
      break;
    case "activity":
      renderActivity();
      break;
    default:
      renderAccount();
  }
}

function renderBreadcrumb() {
  if (els.breadcrumb) {
    els.breadcrumb.textContent = ROUTE_LABELS[state.route] || "商户中心";
  }
}

function renderTopbarStats() {
  const ordersToday = orderData.filter(
    (item) => item.status === "awaiting_accept"
  ).length;
  const target = document.getElementById("today-orders");
  if (target) target.textContent = ordersToday;
}

function renderAccount(options = {}) {
  const { syncFields = false } = options;
  activateTab("account", state.tabs.account);
  if (syncFields || !accountProfileInitialized) {
    renderAccountProfileFields();
    accountProfileInitialized = true;
  }
  updateAccountMetrics();
  updateQuotaPendingNotice();
  renderAccountTimeline();
  renderStaffTable();
}

function renderStaffTable() {
  const keyword = state.staffFilters.keyword.toLowerCase();
  const filtered = staffData.filter((staff) => {
    const matchKeyword = keyword
      ? [staff.name, staff.phone, staff.role]
          .join(" ")
          .toLowerCase()
          .includes(keyword)
      : true;
    const matchStatus =
      state.staffFilters.status === "all" ||
      staff.status === state.staffFilters.status;
    const matchRole =
      state.staffFilters.role === "all" ||
      staff.role === state.staffFilters.role;
    return matchKeyword && matchStatus && matchRole;
  });

  if (!filtered.length) {
    if (els.staffTable) els.staffTable.innerHTML = "";
    if (els.staffEmpty) els.staffEmpty.classList.remove("hidden");
    return;
  }
  if (els.staffEmpty) els.staffEmpty.classList.add("hidden");

  if (els.staffTable)
    els.staffTable.innerHTML = filtered
      .map((staff) => {
        const tagClass =
          staff.status === "active"
            ? "status-tag status-tag--success"
            : "status-tag status-tag--warning";
        const tagLabel = staff.status === "active" ? "正常" : "已暂停";
        const actionButton =
          staff.status === "active"
            ? `<button class="btn btn--ghost" data-action="staff-suspend" data-id="${staff.id}">暂停</button>`
            : `<button class="btn btn--primary" data-action="staff-resume" data-id="${staff.id}">恢复</button>`;
        return `
          <tr>
            <td>${staff.name}</td>
            <td>${staff.phone}</td>
            <td>${staff.role}</td>
            <td><span class="${tagClass}">${tagLabel}</span></td>
            <td>${staff.last}</td>
            <td class="table-actions">
              ${actionButton}
              <button class="btn btn--ghost" data-action="staff-delete" data-id="${staff.id}">删除</button>
            </td>
          </tr>`;
      })
      .join("");
}

function renderProduct() {
  activateTab("product", state.tabs.product);
  renderProductItems();
  renderSalesTabs();
  renderSalesTable();
}

function renderProductItems() {
  const keyword = state.productFilters.keyword.toLowerCase();
  const filtered = productData.filter((product) => {
    const matchKeyword = keyword
      ? [product.name, product.id].join(" ").toLowerCase().includes(keyword)
      : true;
    const matchStatus =
      state.productFilters.status === "all" ||
      product.status === state.productFilters.status;
    const matchType =
      state.productFilters.type === "all" ||
      product.type === state.productFilters.type;
    return matchKeyword && matchStatus && matchType;
  });

  if (!filtered.length) {
    if (els.productTable) els.productTable.innerHTML = "";
    if (els.productEmpty) els.productEmpty.classList.remove("hidden");
    return;
  }
  if (els.productEmpty) els.productEmpty.classList.add("hidden");

  if (els.productTable)
    els.productTable.innerHTML = filtered
      .map((product) => {
        const meta =
          PRODUCT_STATUS_META[product.status] || PRODUCT_STATUS_META.approved;
        const pendingBadge = product.pendingChange
          ? `<span class="badge badge--warning">待审核</span>`
          : "";
        return `
          <tr data-product-row="${product.id}">
            <td>${product.name}</td>
            <td>${product.category}</td>
            <td>${product.price}</td>
            <td>${product.share}</td>
            <td><span class="status-tag status-tag--${meta.tone || "info"}">${
          meta.label
        }</span> ${pendingBadge}</td>
            <td>${product.updatedAt}</td>
            <td class="table-actions">
              <button class="btn btn--ghost" data-action="product-detail" data-id="${
                product.id
              }">详情</button>
              <button class="btn btn--ghost" data-action="product-edit" data-id="${
                product.id
              }">编辑属性</button>
              <button class="btn btn--ghost" data-action="product-change" data-id="${
                product.id
              }">变更申请</button>
            </td>
          </tr>`;
      })
      .join("");
}

function renderSalesTabs() {
  if (!els.salesTabs) return;
  els.salesTabs.innerHTML = SALES_TYPE_META.map(
    (item) => `
      <button class="pill-tabs__item ${
        state.salesType === item.id ? "active" : ""
      }" data-sales-type="${item.id}">${item.label}</button>`
  ).join("");

  els.salesTabs.querySelectorAll("[data-sales-type]").forEach((btn) => {
    btn.addEventListener("click", () => {
      state.salesType = btn.dataset.salesType;
      renderSalesTabs();
      renderSalesTable();
    });
  });
}

function renderSalesTable() {
  if (!els.salesTable) return;
  const filtered = salesData.filter((sale) => {
    if (state.salesType !== sale.type) return false;
    const f = state.salesFilters || {};
    const kw = (f.keyword || "").toLowerCase();
    if (kw && ![sale.product, sale.id].join(" ").toLowerCase().includes(kw))
      return false;
    if (f.status && f.status !== "all" && sale.statusCode !== f.status)
      return false;
    const s = f.start ? new Date(f.start) : null;
    const e = f.end ? new Date(f.end) : null;
    if (s && !isNaN(s) && new Date(sale.end) < s) return false;
    if (e && !isNaN(e) && new Date(sale.start) > e) return false;
    return true;
  });
  if (!filtered.length) {
    els.salesTable.innerHTML = "";
    if (els.salesEmpty) els.salesEmpty.classList.remove("hidden");
    return;
  }
  if (els.salesEmpty) els.salesEmpty.classList.add("hidden");
  els.salesTable.innerHTML = filtered
    .map(
      (sale) => `
        <tr>
          <td>${sale.id}</td>
          <td>${sale.product}</td>
          <td>${
            sale.type === "normal"
              ? "普通"
              : sale.type === "presale"
              ? "预售"
              : "团购"
          }</td>
          <td>${sale.price}</td>
          <td>${sale.start} - ${sale.end}</td>
          <td>${sale.inventory}</td>
          <td><span class="status-tag status-tag--${
            sale.statusCode === "active"
              ? "success"
              : sale.statusCode === "scheduled"
              ? "info"
              : sale.statusCode === "pending"
              ? "warning"
              : sale.statusCode === "offline"
              ? "danger"
              : "info"
          }">${sale.status}</span></td>
          <td class="table-actions">
            <button class="btn btn--ghost" data-action="sales-detail" data-id="${
              sale.id
            }">详情</button>
            <button class="btn btn--ghost" data-action="sales-edit" data-id="${
              sale.id
            }">编辑</button>
            <button class="btn btn--ghost" data-action="sales-copy" data-id="${
              sale.id
            }">复制</button>
            <button class="btn btn--ghost" data-action="sales-delist" data-id="${
              sale.id
            }">下架</button>
            <button class="btn btn--ghost" data-action="sales-delete" data-id="${
              sale.id
            }">删除</button>
          </td>
        </tr>`
    )
    .join("");
}

function renderOrders() {
  renderOrderStatusStrip();
  renderOrderTable();
}

function renderOrderStatusStrip() {
  if (!els.orderStatusStrip) return;
  els.orderStatusStrip.innerHTML = ORDER_STATUS_STRIP.map((item) => {
    const count = orderData.filter((order) => order.status === item.id).length;
    return `
      <div class="status-strip__item" data-order-status="${item.id}">
        <span class="status-strip__title">${item.label}</span>
        <span class="status-strip__count">${count}</span>
      </div>`;
  }).join("");

  els.orderStatusStrip
    .querySelectorAll("[data-order-status]")
    .forEach((card) => {
      card.addEventListener("click", () => {
        state.orderFilters.status = card.dataset.orderStatus;
        renderOrders();
      });
    });
}

function renderOrderTable() {
  if (!els.orderTable) return;
  const filtered = orderData.filter((order) => {
    const matchStatus =
      state.orderFilters.status === "all" ||
      order.status === state.orderFilters.status;
    const keyword = (state.orderFilters.keyword || "").toLowerCase();
    const matchKeyword = keyword
      ? [order.id, order.customer, order.address]
          .join(" ")
          .toLowerCase()
          .includes(keyword)
      : true;
    const matchDate = state.orderFilters.date
      ? (order.createdAt || "").startsWith(state.orderFilters.date)
      : true;
    const matchRegion = state.orderFilters.region
      ? (order.address || "").includes(state.orderFilters.region)
      : true;
    const matchPhone = state.orderFilters.phone
      ? (order.phone || "").includes(state.orderFilters.phone)
      : true;
    return (
      matchStatus && matchKeyword && matchDate && matchRegion && matchPhone
    );
  });

  if (!filtered.length) {
    els.orderTable.innerHTML = "";
    if (els.orderEmpty) els.orderEmpty.classList.remove("hidden");
    return;
  }
  if (els.orderEmpty) els.orderEmpty.classList.add("hidden");

  els.orderTable.innerHTML = filtered
    .map((order) => {
      const meta = ORDER_STATUS_META[order.status] || {
        label: order.status,
        tone: "info",
      };
      const actions = buildOrderActions(order)
        .map(
          (act) =>
            `<button class="btn ${act.style || "btn--ghost"}" data-action="${
              act.action
            }" data-order="${order.id}">${act.label}</button>`
        )
        .join("");
      return `
        <tr data-order-row="${order.id}">
          <td>${order.id}</td>
          <td>${order.customer}</td>
          <td>${order.amount}</td>
          <td>${order.address}</td>
          <td>${order.logistics}</td>
          <td><span class="status-tag status-tag--${meta.tone}">${meta.label}</span></td>
          <td class="table-actions">
            <button class="btn btn--ghost" data-action="order-detail" data-order="${order.id}">详情</button>
            ${actions}
          </td>
        </tr>`;
    })
    .join("");
}

function buildOrderActions(order) {
  const actions = [];
  if (order.status === "awaiting_accept") {
    actions.push({
      label: "接受订单",
      action: "order-accept",
      style: "btn--primary",
    });
    actions.push({ label: "拒绝订单", action: "order-reject" });
  } else if (order.status === "awaiting_ship") {
    actions.push({
      label: "填写发货信息",
      action: "order-ship",
      style: "btn--primary",
    });
    actions.push({ label: "打印面单", action: "order-print-label" });
    actions.push({ label: "取消订单", action: "order-cancel" });
  } else if (order.status === "shipped") {
    actions.push({ label: "打印面单", action: "order-print-label" });
    actions.push({
      label: "标记已完成",
      action: "order-complete",
      style: "btn--primary",
    });
  } else if (order.status === "finished") {
    actions.push({ label: "发起售后", action: "order-create-aftersale" });
  } else if (order.status === "cancelled") {
    actions.push({ label: "查看退款", action: "order-view-refund" });
  }
  return actions;
}

function openOrderDetail(orderId) {
  const order = orderData.find((item) => item.id === orderId);
  if (!order) return;
  const meta = ORDER_STATUS_META[order.status] || {
    label: order.status,
    tone: "info",
  };
  const items = (order.items || [])
    .map((item) => `<li>• ${item.name} × ${item.qty} · ${item.price}</li>`)
    .join("");
  const timeline = (order.timeline || [])
    .map((step) => `<li>• ${step}</li>`)
    .join("");
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">顾客信息</div>
      <div>${order.customer} · ${order.phone}</div>
      <div class="modal-section__minor">${order.address}</div>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">订单概览</div>
      <div>状态：<span class="status-tag status-tag--${meta.tone}">${
    meta.label
  }</span></div>
      <div>金额：${order.amount} · ${order.payment}</div>
      <div>配送方式：${order.logistics}</div>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">商品明细</div>
      <ul class="modal-list">${items || "<li>• 暂无商品信息</li>"}</ul>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">处理记录</div>
      <ul class="modal-list">${timeline || "<li>• 暂无处理历史</li>"}</ul>
    </div>`;
  openModal({
    title: `订单 ${order.id}`,
    body,
    confirmText: "知道了",
    cancelText: "关闭",
  });
}

function openOrderAftersaleForm(orderId) {
  const order = findOrderById(orderId);
  if (!order) return;
  const options = AFTERSALE_TYPE_OPTIONS.map(
    (option) => `<option value="${option.value}">${option.label}</option>`
  ).join("");
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">售后类型</div>
      <label class="form-field">
        <span>申请类型 *</span>
        <select id="aftersale-form-type">${options}</select>
      </label>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">问题说明</div>
      <label class="form-field">
        <span>问题描述 *</span>
        <textarea id="aftersale-form-reason" rows="3" placeholder="请描述顾客诉求（例如外观破损、配件缺失等）"></textarea>
      </label>
      <label class="form-field">
        <span>附件数量</span>
        <input type="number" id="aftersale-form-attachments" min="0" step="1" value="0" />
      </label>
    </div>
  `;
  openModal({
    title: `发起售后 · ${order.id}`,
    body,
    confirmText: "提交售后申请",
    onConfirm: () => {
      const type =
        document.getElementById("aftersale-form-type")?.value || "退款";
      const reason = document
        .getElementById("aftersale-form-reason")
        ?.value.trim();
      const attachments =
        Number(document.getElementById("aftersale-form-attachments")?.value) ||
        0;
      if (!reason) {
        showToast("请填写售后问题描述", "warning");
        return false;
      }
      const newId = `AFS-${Date.now()}`;
      aftersaleData.unshift({
        id: newId,
        customer: order.customer,
        phone: order.phone,
        type,
        status: "pending_review",
        createdAt: formatDateTime(),
        orderId: order.id,
        reason,
        attachments,
        timeline: ["顾客提交售后申请", "等待商户审核"],
        serviceOrder: null,
        source: "order",
      });
      appendOrderTimeline(order, `售后申请 ${newId} 已创建，类型：${type}`);
      showToast(`已提交售后单 ${newId}，请尽快审核`, "success");
      renderAftersales();
      renderOrders();
    },
  });
}

function appendOrderTimeline(order, message) {
  const entry = `${formatDateTime()} · ${message}`;
  order.timeline = [...(order.timeline || []), entry];
}

function openAftersaleLogForm(id) {
  const record = findAftersaleById(id);
  if (!record) return;
  const statusOptions = getNextAftersaleStatusOptions(record.status);
  const selectHtml = statusOptions.length
    ? `<label class="form-field">
        <span>更新状态</span>
        <select id="aftersale-form-status">
          <option value="">保持当前状态</option>
          ${statusOptions
            .map((opt) => `<option value="${opt.value}">${opt.label}</option>`)
            .join("")}
        </select>
      </label>`
    : `<p class="modal-section__minor">当前售后已完成，可补充备注。</p>`;
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">登记处理结果</div>
      ${selectHtml}
      <label class="form-field">
        <span>处理备注 *</span>
        <textarea id="aftersale-form-note" rows="3" placeholder="如：联系顾客安排上门、已与仓库确认换货等"></textarea>
      </label>
    </div>
  `;
  openModal({
    title: `售后处理 · ${record.id}`,
    body,
    confirmText: "登记进展",
    onConfirm: () => {
      const note = document.getElementById("aftersale-form-note")?.value.trim();
      if (!note) {
        showToast("请填写处理备注", "warning");
        return false;
      }
      const nextStatus =
        document.getElementById("aftersale-form-status")?.value || "";
      appendAftersaleTimeline(record, note);
      if (nextStatus) {
        record.status = nextStatus;
        const meta = AFTERSALE_STATUS_META[nextStatus];
        appendAftersaleTimeline(
          record,
          `状态更新为：${meta ? meta.label : nextStatus}`
        );
      }
      record.updatedAt = formatDateTime();
      ensureAftersaleServiceOrder(record);
      showToast(`售后单 ${record.id} 进展已登记`, "success");
      renderAftersales();
    },
  });
}

// 按运单收货功能
// 对应用例 MALL-AFTERSALE-003：商户输入快递单号查询退回的售后商品
// API调用流程：
// 1. GET /shops/{shopId}/aftersales?waybillNo=xxx 查询
// 2. PUT /shops/{shopId}/aftersales/{id}/inspection 验收
function openAftersaleReceiveByWaybill() {
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">按运单号收货</div>
      <p class="modal-section__minor">输入顾客寄回的运单号，查询对应的售后单并进行验收</p>
      <label class="form-field">
        <span>运单号 *</span>
        <input type="text" id="waybill-input" placeholder="例如：SF1234567890、JD9876543210" />
      </label>
    </div>`;
  openModal({
    title: "收货验收入库",
    body,
    confirmText: "查询",
    onConfirm: () => {
      const kw = (document.getElementById("waybill-input")?.value || "").trim().toUpperCase();
      if (!kw) {
        showToast("请输入运单号", "warning");
        return false;
      }
      // 查找匹配的售后单（新数据结构使用 package.waybillNo）
      const rec = aftersaleData.find((afs) => {
        // 检查 package 中的运单号
        if (afs.package && afs.package.waybillNo) {
          return afs.package.waybillNo.toUpperCase().includes(kw);
        }
        // 兼容旧数据结构
        if (afs.serviceOrder && afs.serviceOrder.logistics) {
          return afs.serviceOrder.logistics.toUpperCase().includes(kw);
        }
        return false;
      });
      if (!rec) {
        showToast("未找到匹配的售后单，请检查运单号", "warning");
        return false;
      }
      // 检查状态是否为待验收(1)
      if (String(rec.status) !== "1") {
        const statusLabel = AFTERSALE_STATUS_META[rec.status]?.label || rec.status;
        showToast(`该售后单当前状态为「${statusLabel}」，无需验收`, "info");
        return false;
      }
      openAftersaleReceiveConfirm(rec);
    },
  });
}

// 验收确认弹窗
// 对应 API: PUT /shops/{shopId}/aftersales/{id}/inspection
function openAftersaleReceiveConfirm(record) {
  const waybillNo = record.package?.waybillNo || record.serviceOrder?.logistics || "-";
  const logistics = record.package?.logistics || "";
  const typeLabel = AFTERSALE_TYPE_LABELS[record.type] || record.type;
  
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">售后单信息</div>
      <div>售后单号：${record.id}</div>
      <div>顾客：${record.customer} · ${record.phone}</div>
      <div>售后类型：${typeLabel}</div>
      <div>申请原因：${record.reason}</div>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">物流信息</div>
      <div>运单号：${waybillNo}</div>
      <div>物流公司：${logistics}</div>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">验收操作</div>
      <label class="form-field">
        <span>验收结果 *</span>
        <select id="receive-result">
          <option value="pass">验收通过</option>
          <option value="fail">验收不通过</option>
        </select>
      </label>
      <label class="form-field">
        <span>验收说明</span>
        <textarea id="receive-reason" rows="3" placeholder="验收不通过时必填原因"></textarea>
      </label>
    </div>`;
  openModal({
    title: "验收确认",
    body,
    confirmText: "提交验收",
    onConfirm: () => {
      const result = document.getElementById("receive-result")?.value || "pass";
      const reason = (document.getElementById("receive-reason")?.value || "").trim();
      
      if (result === "pass") {
        // 验收通过：状态 1→4
        record.status = 4; // 已验收
        appendAftersaleTimeline(record, "商户验收通过，等待完成售后处理");
        showToast(`售后单 ${record.id} 验收通过`, "success");
      } else {
        // 验收不通过：状态 1→3
        if (!reason) {
          showToast("请填写验收不通过的原因", "warning");
          return false;
        }
        record.status = 3; // 已取消
        record.cancelReason = reason;
        appendAftersaleTimeline(record, `验收不通过：${reason}`);
        showToast(`售后单 ${record.id} 验收不通过，已取消`, "warning");
      }
      record.updatedAt = formatDateTime();
      renderAftersales();
    },
  });
}

function openAftersaleServiceModal(id) {
  const record = findAftersaleById(id);
  if (!record) return;
  if (record.type === "退款") {
    const body = `
      <div class="modal-section">
        <div class="modal-section__title">退款进度</div>
        <ul class="modal-list">
          ${(record.timeline || [])
            .map((item) => `<li>• ${item}</li>`)
            .join("")}
        </ul>
        <p class="modal-section__minor">退款类售后无需生成服务单，系统将自动同步财务退款状态。</p>
      </div>
    `;
    openModal({
      title: `退款详情 · ${record.id}`,
      body,
      confirmText: "关闭",
      cancelText: " ",
      onConfirm: () => {},
    });
    return;
  }
  const service = ensureAftersaleServiceOrder(record);
  const steps =
    (service.steps || []).map((step) => `<li>• ${step}</li>`).join("") ||
    "<li>• 暂无服务进度</li>";
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">服务单信息</div>
      <div>服务单号：${service.id}</div>
      <div>类型：${service.type}</div>
      <div>指派人：${service.assigned}</div>
      <div>当前状态：${service.status}</div>
      ${service.logistics ? `<div>物流信息：${service.logistics}</div>` : ""}
    </div>
    <div class="modal-section">
      <div class="modal-section__title">处理步骤</div>
      <ul class="modal-list">${steps}</ul>
    </div>
    ${
      service.report
        ? `<div class="modal-section">
            <div class="modal-section__title">履约报告</div>
            <p>${service.report}</p>
          </div>`
        : ""
    }
  `;
  openModal({
    title: `售后服务单 · ${service.id}`,
    body,
    confirmText: "关闭",
    cancelText: " ",
    onConfirm: () => {},
  });
}

function renderAftersales() {
  renderAftersaleStatusTabs();
  renderAftersaleTable();
}

function renderAftersaleStatusTabs() {
  if (!els.aftersaleStatus) return;
  const visibleFilters = AFTERSALE_FILTERS.filter((item) => !item.hidden);
  els.aftersaleStatus.innerHTML = visibleFilters.map((item) => {
    const count = aftersaleData.filter((afs) => String(afs.status) === item.id).length;
    return `
      <button class="pill-tabs__item ${
        state.aftersaleFilters.status === item.id ? "active" : ""
      }" data-aftersale-status="${item.id}">
        ${item.label} (${count})
      </button>`;
  }).join("");

  els.aftersaleStatus
    .querySelectorAll("[data-aftersale-status]")
    .forEach((btn) => {
      btn.addEventListener("click", () => {
        state.aftersaleFilters.status = btn.dataset.aftersaleStatus;
        renderAftersales();
      });
    });
}

function renderAftersaleTable() {
  if (!els.aftersaleTable) return;
  const keyword = (state.aftersaleFilters.keyword || "").toLowerCase();
  const waybillKw = (state.aftersaleFilters.waybill || "").toLowerCase();
  const filtered = aftersaleData.filter((item) => {
    const matchStatus =
      state.aftersaleFilters.status === "all" ||
      String(item.status) === String(state.aftersaleFilters.status);
    const matchKeyword = keyword
      ? [item.id, item.customer, item.orderId]
          .join(" ")
          .toLowerCase()
          .includes(keyword)
      : true;
    const filterType = state.aftersaleFilters.type;
    const matchType =
      filterType === "all" ||
      String(item.type) === String(filterType) ||
      (AFTERSALE_TYPE_LABELS[item.type] && AFTERSALE_TYPE_LABELS[item.type] === AFTERSALE_TYPE_LABELS[filterType]);
    const matchPhone = state.aftersaleFilters.phone
      ? item.phone.includes(state.aftersaleFilters.phone)
      : true;
    const logisticsStr =
      (item.serviceOrder && item.serviceOrder.logistics) || "";
    const matchWaybill = waybillKw
      ? logisticsStr.toLowerCase().includes(waybillKw)
      : true;
    return (
      matchStatus && matchKeyword && matchType && matchPhone && matchWaybill
    );
  });

  if (!filtered.length) {
    els.aftersaleTable.innerHTML = "";
    if (els.aftersaleEmpty) els.aftersaleEmpty.classList.remove("hidden");
    return;
  }
  if (els.aftersaleEmpty) els.aftersaleEmpty.classList.add("hidden");

  els.aftersaleTable.innerHTML = filtered
    .map((item) => {
      const meta =
        AFTERSALE_STATUS_META[item.status] ||
        AFTERSALE_STATUS_META.pending_review;
      const actions = buildAftersaleActions(item)
        .map(
          (act) =>
            `<button class="btn ${act.style || "btn--ghost"}" data-action="${
              act.action
            }" data-id="${item.id}">${act.label}</button>`
        )
        .join("");
      const typeLabel = AFTERSALE_TYPE_LABELS[item.type] || item.type;
      return `
        <tr data-aftersale-row="${item.id}">
          <td>${item.id}</td>
          <td>${item.customer}</td>
          <td>${item.createdAt}</td>
          <td>${typeLabel}</td>
          <td><span class="status-tag status-tag--${meta.tone}">${meta.label}</span></td>
          <td class="table-actions">
            <button class="btn btn--ghost" data-action="aftersale-detail" data-id="${item.id}">详情</button>
            ${actions}
          </td>
        </tr>`;
    })
    .join("");
}

function buildAftersaleActions(record) {
  const actions = [];
  const status = String(record.status);
  
  // 0-待审核：审核通过、驳回申请
  if (status === "0" || status === "pending_review") {
    actions.push({
      label: "审核通过",
      action: "aftersale-approve",
      style: "btn--primary",
    });
    actions.push({ label: "驳回申请", action: "aftersale-reject" });
  } 
  // 1-待验收：验收通过、验收不通过
  else if (status === "1") {
    actions.push({
      label: "验收通过",
      action: "aftersale-inspect-pass",
      style: "btn--primary",
    });
    actions.push({ label: "验收不通过", action: "aftersale-inspect-fail" });
    actions.push({ label: "登记备注", action: "aftersale-log" });
  }
  // 2-待上门：验收通过、验收不通过
  else if (status === "2") {
    actions.push({
      label: "验收通过",
      action: "aftersale-inspect-pass",
      style: "btn--primary",
    });
    actions.push({ label: "验收不通过", action: "aftersale-inspect-fail" });
    actions.push({ label: "查看服务单", action: "aftersale-service" });
  }
  // 4-已验收：完成售后、取消售后
  else if (status === "4") {
    actions.push({
      label: "完成售后",
      action: "aftersale-complete",
      style: "btn--primary",
    });
    actions.push({ label: "取消售后", action: "aftersale-cancel" });
    actions.push({ label: "登记备注", action: "aftersale-log" });
  }
  // 5-维修中：完成维修、取消维修
  else if (status === "5") {
    actions.push({
      label: "完成维修",
      action: "aftersale-complete",
      style: "btn--primary",
    });
    actions.push({ label: "取消维修", action: "aftersale-cancel" });
    actions.push({ label: "查看服务单", action: "aftersale-service" });
  }
  // 6-已完成、3-已取消：只读
  else if (status === "6" || status === "3" || status === "finished") {
    actions.push({ label: "查看服务单", action: "aftersale-service" });
  }
  // 兼容旧状态
  else if (status === "in_progress") {
    actions.push({ label: "登记处理结果", action: "aftersale-log" });
    actions.push({ label: "查看服务单", action: "aftersale-service" });
  } else if (status === "waiting_receipt") {
    actions.push({
      label: "确认收货",
      action: "aftersale-confirm",
      style: "btn--primary",
    });
    actions.push({ label: "查看服务单", action: "aftersale-service" });
  }
  return actions;
}

function openAftersaleDetail(id) {
  const data = aftersaleData.find((item) => item.id === id);
  if (!data) return;
  const meta = AFTERSALE_STATUS_META[data.status] || { label: data.status, tone: "info" };
  const typeLabel = AFTERSALE_TYPE_LABELS[data.type] || data.type;
  
  // 物流信息
  const packageInfo = data.package ? `
    <div class="modal-section">
      <div class="modal-section__title">物流信息</div>
      <div>运单号：${data.package.waybillNo}</div>
      <div>物流公司：${data.package.logistics}</div>
      <div>类型：${data.package.type === 0 ? "商家寄顾客" : "顾客寄商家"}</div>
    </div>` : "";
  
  // 服务单信息
  const serviceInfo = data.serviceOrder ? `
    <div class="modal-section">
      <div class="modal-section__title">服务单信息</div>
      <div>服务单号：${data.serviceOrder.id}</div>
      <div>类型：${data.serviceOrder.type}</div>
      <div>指派人：${data.serviceOrder.assigned}</div>
      <div>状态：${data.serviceOrder.status}</div>
      ${data.serviceOrder.appointmentTime ? `<div>预约时间：${data.serviceOrder.appointmentTime}</div>` : ""}
      ${data.serviceOrder.report ? `<div>维修报告：${data.serviceOrder.report}</div>` : ""}
    </div>` : "";
  
  // 取消原因
  const cancelInfo = data.cancelReason ? `
    <div class="modal-section">
      <div class="modal-section__title">取消原因</div>
      <div>${data.cancelReason}</div>
    </div>` : "";

  const body = `
    <div class="modal-section">
      <div class="modal-section__title">顾客信息</div>
      <div>${data.customer} · ${data.phone}</div>
      <div class="modal-section__minor">关联订单：${data.orderId}</div>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">售后概览</div>
      <div>类型：${typeLabel}</div>
      <div>状态：<span class="status-tag status-tag--${meta.tone}">${meta.label}</span></div>
      <div>申请时间：${data.createdAt}</div>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">问题描述</div>
      <div>${data.reason}</div>
      <div class="modal-section__minor">附件数量：${data.attachments || 0}</div>
    </div>
    ${packageInfo}
    ${serviceInfo}
    ${cancelInfo}
    <div class="modal-section">
      <div class="modal-section__title">处理记录</div>
      <ul class="modal-list">${
        (data.timeline || []).map((item) => `<li>• ${item}</li>`).join("") ||
        "<li>• 暂无处理记录</li>"
      }</ul>
    </div>`;
  openModal({
    title: `售后单 ${data.id}`,
    body,
    confirmText: "知道了",
    cancelText: "关闭",
  });
}

function acceptOrder(orderId) {
  const order = orderData.find((item) => item.id === orderId);
  if (!order) return;
  if (order.status !== "awaiting_accept") {
    showToast("当前状态不可执行接受操作", "warning");
    return;
  }
  // 生成运单草稿（将在发货时补充运单号与重量）
  order.status = "awaiting_ship";
  order.waybill = order.waybill || {};
  order.waybill.createdAt = formatDateTime();
  order.timeline = [
    ...(order.timeline || []),
    "商户已接受订单，运单草稿已生成，待安排发货",
  ];
  showToast(`订单 ${orderId} 已接受`, "success");
  renderOrders();
}

function openOrderReject(orderId) {
  const order = orderData.find((item) => item.id === orderId);
  if (!order) return;
  openModal({
    title: "拒绝订单",
    body: `<p>确认拒绝订单 <strong>${orderId}</strong> 吗？系统将自动取消并发起退款。</p>`,
    confirmText: "确认拒绝",
    onConfirm: () => {
      order.status = "cancelled";
      order.timeline = [
        ...(order.timeline || []),
        "商户拒绝订单，已通知平台退款",
      ];
      showToast(`订单 ${orderId} 已拒绝并触发退款流程`, "warning");
      renderOrders();
    },
  });
}

function openOrderShipForm(orderId) {
  const order = orderData.find((item) => item.id === orderId);
  if (!order) return;
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">发货信息</div>
      <label class="form-field">
        <span>物流公司</span>
        <input type="text" id="ship-company" value="${
          order.logistics || ""
        }" placeholder="例如 顺丰速运" />
      </label>
      <label class="form-field">
        <span>运单号</span>
        <input type="text" id="ship-tracking" placeholder="请输入运单号" />
      </label>
      <label class="form-field">
        <span>包裹重量 (kg)</span>
        <input type="number" id="ship-weight" min="0" step="0.1" />
      </label>
    </div>`;
  openModal({
    title: `订单 ${orderId} 发货`,
    body,
    confirmText: "确认发货",
    onConfirm: () => {
      if (order.status !== "awaiting_ship") {
        showToast("当前状态不可发货", "warning");
        return false;
      }
      const company = document.getElementById("ship-company")?.value.trim();
      const tracking = document.getElementById("ship-tracking")?.value.trim();
      const weight = Number(document.getElementById("ship-weight")?.value);
      if (!tracking) {
        showToast("请填写运单号", "warning");
        return false;
      }
      order.logistics = company || order.logistics || "顺丰速运";
      order.waybill = {
        number: tracking,
        weight: Number.isNaN(weight) ? undefined : weight,
        company: order.logistics,
        shippedAt: formatDateTime(),
      };
      order.status = "shipped";
      order.timeline = [...(order.timeline || []), "商户已发货，等待物流揽收"];
      showToast(`订单 ${orderId} 已发货`, "success");
      renderOrders();
    },
  });
}

function openOrderPrintLabel(orderId) {
  const order = orderData.find((item) => item.id === orderId);
  if (!order) return;
  const wb = order.waybill || {};
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">面单预览</div>
      <div class="waybill">
        <div>订单号：${order.id}</div>
        <div>收件人：${order.customer} · ${order.phone || ""}</div>
        <div>地址：${order.address || ""}</div>
        <div>物流公司：${order.logistics || "-"}</div>
        <div>运单号：${wb.number || "(未填写)"}</div>
        <div>重量：${wb.weight != null ? wb.weight + " kg" : "-"}</div>
      </div>
      <p class="modal-section__minor">请确认信息无误后进行打印。</p>
    </div>`;
  openModal({
    title: `打印面单 · ${orderId}`,
    body,
    confirmText: "打印",
    cancelText: "关闭",
    onConfirm: () => {
      showToast("已发送到打印机（模拟）", "success");
    },
  });
}

function completeOrder(orderId) {
  const order = orderData.find((item) => item.id === orderId);
  if (!order) return;
  order.status = "finished";
  order.timeline = [...(order.timeline || []), "订单标记完成，等待售后观察期"];
  showToast(`订单 ${orderId} 已完成履约`, "success");
  renderOrders();
}

function approveAftersale(id) {
  const record = aftersaleData.find((item) => item.id === id);
  if (!record) return;
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">审核通过并设置类型</div>
      <label class="form-field">
        <span>售后类型</span>
        <select id="aftersale-approve-type">
          <option value="refund" ${
            record.type === "refund" ? "selected" : ""
          }>退款</option>
          <option value="return" ${
            record.type === "return" ? "selected" : ""
          }>退货</option>
          <option value="exchange" ${
            record.type === "exchange" ? "selected" : ""
          }>换货</option>
          <option value="repair" ${
            record.type === "repair" ? "selected" : ""
          }>维修</option>
        </select>
      </label>
      <label class="form-field">
        <span>处理说明（可选）</span>
        <textarea id="aftersale-approve-note" rows="3" placeholder="如：通过审核，安排上门取件或生成物流单"></textarea>
      </label>
    </div>`;
  openModal({
    title: "审核售后申请",
    body,
    confirmText: "确认通过",
    onConfirm: () => {
      const newType =
        document.getElementById("aftersale-approve-type")?.value || record.type;
      const note = (
        document.getElementById("aftersale-approve-note")?.value || ""
      ).trim();
      record.type = newType;
      record.status = "in_progress";
      appendAftersaleTimeline(
        record,
        `审核通过（类型：${newType}）${note ? " - " + note : ""}`
      );
      // 创建待审核状态的服务单（状态图：0-PENDING_REVIEW）
      createServiceOrderForAftersale(record);
      record.updatedAt = formatDateTime();
      showToast(`售后单 ${id} 已审核通过，服务单已创建待商户审核`, "success");
      renderAftersales();
    },
  });
}

// 新增：为售后单创建服务单（初始状态为pending_review-待商户审核）
function createServiceOrderForAftersale(record) {
  if (record.type === "退款" || record.type === "refund") {
    return null;
  }
  if (!record.serviceOrder) {
    const baseId =
      record.type === "维修" || record.type === "repair"
        ? "SO-REP"
        : record.type === "换货" || record.type === "exchange"
        ? "SO-EXC"
        : "SO-RET";
    const serviceOrderId = `${baseId}-${Date.now()}`;
    
    // 创建服务单对象（状态为pending_review-待商户审核）
    record.serviceOrder = {
      id: serviceOrderId,
      aftersaleId: record.id,
      orderId: record.orderId,
      type:
        record.type === "维修" || record.type === "repair"
          ? "寄修"
          : record.type === "换货" || record.type === "exchange"
          ? "上门换货"
          : "上门取件",
      serviceCategory: record.type === "维修" || record.type === "repair" ? "家电维修" : "售后服务",
      status: "pending_review", // 初始状态：待商户审核
      merchant: "星河数码旗舰店", // 从售后单获取商户信息
      region: "上海 徐汇", // 从售后单获取地区信息
      customer: {
        name: record.customer,
        phone: record.phone,
        address: record.address || "待补充"
      },
      product: record.product || "待补充",
      notes: record.reason,
      priority: "中",
      requireReceipt: record.type === "维修" || record.type === "repair",
      received: false,
      waybillNumber: "",
      assignedTo: null,
      expectedFinish: null,
      timeline: [
        { time: formatDateTime(), text: "商户审核售后通过，创建服务单", actor: "系统" },
        { time: formatDateTime(), text: "等待商户审核服务单", actor: "系统" }
      ],
      createdAt: formatDateTime()
    };
    
    appendAftersaleTimeline(record, `已创建服务单 ${serviceOrderId}，等待商户审核`);
  }
  return record.serviceOrder;
}

function rejectAftersale(id) {
  const record = aftersaleData.find((item) => item.id === id);
  if (!record) return;
  openModal({
    title: "驳回售后申请",
    body: `
      <p>确认驳回售后单 <strong>${id}</strong> 吗？请填写驳回原因。</p>
      <label class="form-field">
        <span>驳回原因 *</span>
        <textarea id="aftersale-reject-reason" rows="3" placeholder="例如：超出售后期、商品已使用等"></textarea>
      </label>
    `,
    confirmText: "确认驳回",
    onConfirm: () => {
      record.status = "finished";
      const rejectReason = document
        .getElementById("aftersale-reject-reason")
        ?.value.trim();
      appendAftersaleTimeline(
        record,
        rejectReason ? `商户驳回售后申请：${rejectReason}` : "商户驳回售后申请"
      );
      record.updatedAt = formatDateTime();
      showToast(`售后单 ${id} 已驳回`, "warning");
      renderAftersales();
    },
  });
}

function logAftersaleProgress(id) {
  openAftersaleLogForm(id);
}

function confirmAftersaleReceipt(id) {
  const record = aftersaleData.find((item) => item.id === id);
  if (!record) return;
  record.status = "finished";
  appendAftersaleTimeline(record, "已确认收货，售后关闭");
  const service = ensureAftersaleServiceOrder(record);
  if (service) {
    service.status = "已完成";
    service.steps = [
      ...(service.steps || []),
      `${formatDateTime()} · 顾客已确认完成`,
    ];
  }
  record.updatedAt = formatDateTime();
  showToast(`售后单 ${id} 已确认收货`, "success");
  renderAftersales();
}

// 验收售后商品（对应API: PUT /shops/{shopId}/aftersales/{id}/inspection）
function inspectAftersale(id, passed) {
  const record = aftersaleData.find((item) => item.id === id);
  if (!record) return;
  
  if (passed) {
    // 验收通过
    const status = String(record.status);
    if (status === "1") {
      // 待验收 → 已验收
      record.status = "4";
      appendAftersaleTimeline(record, "商品验收通过，等待完成售后");
      showToast(`售后单 ${id} 验收通过`, "success");
    } else if (status === "2") {
      // 待上门 → 维修中
      record.status = "5";
      appendAftersaleTimeline(record, "上门验收通过，开始维修");
      showToast(`售后单 ${id} 开始维修`, "success");
    }
  } else {
    // 验收不通过，弹窗填写原因
    openModal({
      title: "验收不通过",
      body: `<div class="modal-section">
        <label class="form-field">
          <span>不通过原因 *</span>
          <textarea id="inspect-fail-reason" rows="3" placeholder="请填写验收不通过的原因"></textarea>
        </label>
      </div>`,
      confirmText: "确认",
      onConfirm: () => {
        const reason = document.getElementById("inspect-fail-reason")?.value.trim();
        if (!reason) {
          showToast("请填写不通过原因", "warning");
          return false;
        }
        record.status = "3";
        appendAftersaleTimeline(record, `验收不通过：${reason}`);
        record.updatedAt = formatDateTime();
        showToast(`售后单 ${id} 已取消`, "warning");
        renderAftersales();
      },
    });
    return;
  }
  record.updatedAt = formatDateTime();
  renderAftersales();
}

// 完成售后（对应API: PUT /shops/{shopId}/aftersales/{id}/complete）
function completeAftersale(id) {
  const record = aftersaleData.find((item) => item.id === id);
  if (!record) return;
  
  openModal({
    title: "完成售后",
    body: `<div class="modal-section">
      <p>确认完成售后单 <strong>${id}</strong> 吗？</p>
      <label class="form-field">
        <span>处理结论（可选）</span>
        <textarea id="complete-conclusion" rows="2" placeholder="填写处理结论"></textarea>
      </label>
    </div>`,
    confirmText: "确认完成",
    onConfirm: () => {
      const conclusion = document.getElementById("complete-conclusion")?.value.trim();
      record.status = "6";
      appendAftersaleTimeline(record, conclusion ? `售后完成：${conclusion}` : "售后已完成");
      const service = ensureAftersaleServiceOrder(record);
      if (service) {
        service.status = "已完成";
        service.steps = [...(service.steps || []), `${formatDateTime()} · 售后完成`];
      }
      record.updatedAt = formatDateTime();
      showToast(`售后单 ${id} 已完成`, "success");
      renderAftersales();
    },
  });
}

// 取消售后（对应API: PUT /shops/{shopId}/aftersales/{id}/cancel）
function cancelAftersale(id) {
  const record = aftersaleData.find((item) => item.id === id);
  if (!record) return;
  
  openModal({
    title: "取消售后",
    body: `<div class="modal-section">
      <p>确认取消售后单 <strong>${id}</strong> 吗？</p>
      <label class="form-field">
        <span>取消原因 *</span>
        <textarea id="cancel-reason" rows="3" placeholder="请填写取消原因"></textarea>
      </label>
    </div>`,
    confirmText: "确认取消",
    onConfirm: () => {
      const reason = document.getElementById("cancel-reason")?.value.trim();
      if (!reason) {
        showToast("请填写取消原因", "warning");
        return false;
      }
      record.status = "3";
      record.cancelReason = reason;
      appendAftersaleTimeline(record, `售后已取消：${reason}`);
      record.updatedAt = formatDateTime();
      showToast(`售后单 ${id} 已取消`, "warning");
      renderAftersales();
    },
  });
}

function renderFinance() {
  activateTab("finance", state.tabs.finance);
  renderPaymentTable();
  renderRefundTable();
}

function renderPaymentTable() {
  if (!els.paymentTable) return;
  const keyword = (state.paymentFilters.keyword || "").toLowerCase();
  const filtered = paymentData.filter((item) => {
    const matchChannel =
      state.paymentFilters.channel === "all" ||
      (item.channel.includes("微信") &&
        state.paymentFilters.channel === "wechat") ||
      (item.channel.includes("支付宝") &&
        state.paymentFilters.channel === "alipay") ||
      (item.channel.includes("银联") &&
        state.paymentFilters.channel === "unionpay");

    const matchKeyword = keyword
      ? [item.id, item.order].join(" ").toLowerCase().includes(keyword)
      : true;

    const matchDate = state.paymentFilters.date
      ? (item.time || "").startsWith(state.paymentFilters.date)
      : true;

    let matchAmount = true;
    const range = (state.paymentFilters.amount || "").replace(/[^\d\-.]/g, "");
    if (range) {
      const amt = Number((item.amount || "").replace(/[^\d.]/g, ""));
      if (range.includes("-")) {
        const [min, max] = range.split("-").map((v) => Number(v.trim()));
        matchAmount = (isNaN(min) || amt >= min) && (isNaN(max) || amt <= max);
      } else {
        const min = Number(range);
        matchAmount = !isNaN(min) ? amt >= min : true;
      }
    }
    return matchChannel && matchKeyword && matchDate && matchAmount;
  });

  if (!filtered.length) {
    els.paymentTable.innerHTML = "";
    if (els.paymentEmpty) els.paymentEmpty.classList.remove("hidden");
    return;
  }
  if (els.paymentEmpty) els.paymentEmpty.classList.add("hidden");

  els.paymentTable.innerHTML = filtered
    .map(
      (item) => `
        <tr>
          <td>${item.id}</td>
          <td>${item.order}</td>
          <td>${item.time}</td>
          <td>${item.amount}</td>
          <td>${item.channel}</td>
          <td>${item.share}</td>
          <td class="table-actions">
            <button class="btn btn--ghost" data-action="payment-detail" data-id="${item.id}">明细</button>
          </td>
        </tr>`
    )
    .join("");
}

function renderRefundTable() {
  if (!els.refundTable) return;
  const keyword = (state.refundFilters.keyword || "").toLowerCase();
  const filtered = refundData.filter((item) => {
    const matchKeyword = keyword
      ? [item.id, item.paymentId].join(" ").toLowerCase().includes(keyword)
      : true;
    const matchDate = state.refundFilters.date
      ? (item.time || "").startsWith(state.refundFilters.date)
      : true;
    let matchAmount = true;
    const range = (state.refundFilters.amount || "").replace(/[^\d\-.]/g, "");
    if (range) {
      const amt = Number((item.amount || "").replace(/[^\d.]/g, ""));
      if (range.includes("-")) {
        const [min, max] = range.split("-").map((v) => Number(v.trim()));
        matchAmount = (isNaN(min) || amt >= min) && (isNaN(max) || amt <= max);
      } else {
        const min = Number(range);
        matchAmount = !isNaN(min) ? amt >= min : true;
      }
    }
    return matchKeyword && matchDate && matchAmount;
  });

  if (!filtered.length) {
    els.refundTable.innerHTML = "";
    if (els.refundEmpty) els.refundEmpty.classList.remove("hidden");
    return;
  }
  if (els.refundEmpty) els.refundEmpty.classList.add("hidden");

  els.refundTable.innerHTML = filtered
    .map(
      (item) => `
        <tr>
          <td>${item.id}</td>
          <td>${item.paymentId}</td>
          <td>${item.time}</td>
          <td>${item.amount}</td>
          <td>${item.share}</td>
          <td class="table-actions">
            <button class="btn btn--ghost" data-action="refund-detail" data-id="${item.id}">明细</button>
          </td>
        </tr>`
    )
    .join("");
}

function openPaymentDetailModal(id) {
  const record = findPaymentById(id);
  if (!record) return;
  const relatedRefunds = refundData.filter(
    (item) => item.paymentId === record.id
  );
  const refundList = relatedRefunds.length
    ? relatedRefunds
        .map((item) => `<li>• ${item.id} · ${item.amount} · ${item.share}</li>`)
        .join("")
    : "<li>• 暂无关联退款</li>";
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">支付信息</div>
      <div>订单号：${record.order}</div>
      <div>支付渠道：${record.channel}</div>
      <div>支付时间：${record.time}</div>
      <div>支付金额：${record.amount}</div>
      <div>分账状态：${record.share}</div>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">关联退款</div>
      <ul class="modal-list">${refundList}</ul>
    </div>
  `;
  openModal({
    title: `支付明细 · ${record.id}`,
    body,
    confirmText: "关闭",
    cancelText: " ",
    onConfirm: () => {},
  });
}

function openRefundDetailModal(id) {
  const record = findRefundById(id);
  if (!record) return;
  const payment = findPaymentById(record.paymentId);
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">退款信息</div>
      <div>退款单号：${record.id}</div>
      <div>退款时间：${record.time}</div>
      <div>退款金额：${record.amount}</div>
      <div>分账状态：${record.share}</div>
    </div>
    <div class="modal-section">

      <div class="modal-section__title">关联支付单</div>
      <div>${record.paymentId}${
    payment ? ` · ${payment.amount} · ${payment.channel}` : ""
  }</div>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">备注</div>
      <p class="modal-section__minor">平台将在 24 小时内完成退款入账，分账金额会随退款同步退回。</p>
    </div>
  `;
  openModal({
    title: `退款明细 · ${record.id}`,
    body,
    confirmText: "关闭",
    cancelText: " ",
    onConfirm: () => {},
  });
}

function renderServices() {
  const f = state.serviceFilters || {};
  let filtered = serviceData.slice();
  if (f.keyword) {
    const kw = f.keyword.toLowerCase();
    filtered = filtered.filter((item) =>
      [item.name, item.id, item.type].join(" ").toLowerCase().includes(kw)
    );
  }
  if (f.type) {
    const t = f.type.toLowerCase();
    filtered = filtered.filter((item) =>
      (item.type || "").toLowerCase().includes(t)
    );
  }
  if (f.product) {
    const pk = f.product.toLowerCase();
    filtered = filtered.filter((item) =>
      (item.products || []).some((p) => (p || "").toLowerCase().includes(pk))
    );
  }
  if (f.status && f.status !== "all") {
    filtered = filtered.filter(
      (item) => (item.status || "pending") === f.status
    );
  }
  if (f.region) {
    const rk = f.region.toLowerCase();
    filtered = filtered.filter((item) =>
      (item.regions || []).some((r) => (r || "").toLowerCase().includes(rk))
    );
  }

  if (!filtered.length) {
    if (els.serviceTable) els.serviceTable.innerHTML = "";
    if (els.serviceEmpty) els.serviceEmpty.classList.remove("hidden");
    return;
  }
  if (els.serviceEmpty) els.serviceEmpty.classList.add("hidden");

  if (els.serviceTable)
    els.serviceTable.innerHTML = filtered
      .map(
        (item) => `
        <tr data-service-row="${item.id}">
          <td>${item.name}</td>
          <td>${item.type}</td>
          <td>${(item.regions || []).join("、")}</td>
          <td>${(item.products || []).join("、")}</td>
          <td>${
            item.status === "active"
              ? "生效中"
              : item.status === "pending"
              ? "待审核"
              : item.status
          }</td>
          <td class="table-actions">
            <button class="btn btn--ghost" data-action="service-detail" data-id="${
              item.id
            }">详情</button>
            <button class="btn btn--ghost" data-action="service-edit" data-id="${
              item.id
            }">编辑</button>
            <button class="btn btn--ghost" data-action="service-history" data-id="${
              item.id
            }">审核记录</button>
            <button class="btn btn--ghost" data-action="service-delete" data-id="${
              item.id
            }">删除</button>
          </td>
        </tr>`
      )
      .join("");
}

function openServiceDetail(id) {
  const service = serviceData.find((item) => item.id === id);
  if (!service) return;
  const audits = (service.audits || [])
    .map((audit) => `<li>• ${audit.time} · ${audit.result}</li>`)
    .join("");
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">服务概览</div>
      <div>${service.name}</div>
      <div class="modal-section__minor">类型：${service.type} · 状态：${
    service.status === "active" ? "生效中" : "待审核"
  }</div>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">适用信息</div>
      <div>适用商品：${service.products.join("、")}</div>
      <div>服务地区：${service.regions.join("、")}</div>
      <div>定价：${service.price}</div>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">说明</div>
      <div>${service.description}</div>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">审核记录</div>
      <ul class="modal-list">${audits || "<li>• 暂无审核记录</li>"}</ul>
    </div>`;
  openModal({
    title: `服务 ${service.id}`,
    body,
    confirmText: "知道了",
    cancelText: "关闭",
  });
}

function openServiceEditForm(id) {
  const service = findServiceById(id);
  if (!service) return;
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">服务基础信息</div>
      <label class="form-field">
        <span>服务名称 *</span>
        <input type="text" id="service-form-name" value="${service.name}" />
      </label>
      <label class="form-field">
        <span>服务价格 *</span>
        <input type="text" id="service-form-price" value="${service.price}" />
      </label>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">适用范围</div>
      <label class="form-field">
        <span>服务区域（以逗号分隔）</span>
        <input type="text" id="service-form-regions" value="${service.regions.join(
          "、"
        )}" />
      </label>
      <label class="form-field">
        <span>关联商品（以逗号分隔）</span>
        <input type="text" id="service-form-products" value="${service.products.join(
          "、"
        )}" />
      </label>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">服务说明</div>
      <textarea id="service-form-description" rows="3">${
        service.description
      }</textarea>
    </div>
  `;
  openModal({
    title: `编辑服务 · ${service.id}`,
    body,
    confirmText: "保存",
    onConfirm: () => {
      const name = document.getElementById("service-form-name")?.value.trim();
      const price = document.getElementById("service-form-price")?.value.trim();
      if (!name || !price) {
        showToast("请填写服务名称与价格", "warning");
        return false;
      }
      service.name = name;
      service.price = price;
      const regionsValue =
        document.getElementById("service-form-regions")?.value.trim() || "";
      service.regions = regionsValue
        ? regionsValue
            .split(/[、,，]/)
            .map((item) => item.trim())
            .filter(Boolean)
        : [];
      const productsValue =
        document.getElementById("service-form-products")?.value.trim() || "";
      service.products = productsValue
        ? productsValue
            .split(/[、,，]/)
            .map((item) => item.trim())
            .filter(Boolean)
        : [];
      service.description =
        document.getElementById("service-form-description")?.value.trim() ||
        service.description;
      service.updatedAt = formatDateTime();
      showToast(`服务 ${service.id} 已更新`, "success");
      refreshServiceTable();
    },
  });
}

function openServiceHistoryModal(id) {
  const service = findServiceById(id);
  if (!service) return;
  const historyList =
    (service.audits || [])
      .map((audit) => `<li>• ${audit.time} · ${audit.result}</li>`)
      .join("") || "<li>• 暂无审核记录</li>";
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">审核记录</div>
      <ul class="modal-list">${historyList}</ul>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">新增记录</div>
      <label class="form-field">
        <span>处理结果</span>
        <input type="text" id="service-history-result" placeholder="例如：平台通过审核" />
      </label>
    </div>
  `;
  openModal({
    title: `审核记录 · ${service.id}`,
    body,
    confirmText: "保存记录",
    onConfirm: () => {
      const result = document
        .getElementById("service-history-result")
        ?.value.trim();
      if (result) {
        service.audits = [
          ...(service.audits || []),
          { time: formatDateTime(), result },
        ];
        service.updatedAt = formatDateTime();
        showToast("已追加审核记录", "success");
        refreshServiceTable();
      } else {
        showToast("未填写新的审核记录，已关闭窗口", "info");
      }
    },
  });
}

function renderPartner() {
  activateTab("partner", state.tabs.partner);
  renderProviderTable();
  renderContractTable();
}

function openServiceCreateForm() {
  const approvedProducts = (productData || []).filter(
    (p) => p.status === "approved"
  );
  const options = approvedProducts
    .map((p) => `<option value="${p.name}">${p.name}</option>`)
    .join("");
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">服务基础信息</div>
      <label class="form-field">
        <span>服务名称 *</span>
        <input type="text" id="service-new-name" placeholder="例如：上门安装" />
      </label>
      <label class="form-field">
        <span>服务类型 *</span>
        <input type="text" id="service-new-type" placeholder="安装/维修/保养" />
      </label>
      <label class="form-field">
        <span>服务价格</span>
        <input type="text" id="service-new-price" placeholder="例如：¥ 99" />
      </label>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">适用范围</div>
      <label class="form-field">
        <span>服务地区（以逗号或顿号分隔）</span>
        <input type="text" id="service-new-regions" placeholder="例如：上海、苏州" />
      </label>
      <label class="form-field">
        <span>关联商品（多选）*</span>
        <select id="service-new-products" multiple size="6">${options}</select>
      </label>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">服务说明</div>
      <textarea id="service-new-description" rows="3" placeholder="补充说明"></textarea>
    </div>
  `;
  openModal({
    title: "新建服务",
    body,
    confirmText: "提交审核",
    onConfirm: () => {
      const name = document.getElementById("service-new-name")?.value.trim();
      const type = document.getElementById("service-new-type")?.value.trim();
      const price =
        document.getElementById("service-new-price")?.value.trim() || "¥ 0";
      const regionsValue =
        document.getElementById("service-new-regions")?.value.trim() || "";
      const productsEl = document.getElementById("service-new-products");
      const selected = Array.from(productsEl?.selectedOptions || []).map(
        (o) => o.value
      );
      if (!name || !type) {
        showToast("请填写服务名称与类型", "warning");
        return false;
      }
      // 用例001扩展场景3b：未选择适用的商品
      if (!selected.length) {
        showToast("必须选择至少一个适用的商品", "warning");
        return false;
      }
      
      // 用例001扩展场景3c：选择的商品不存在或已下架
      const invalid = selected.filter(
        (n) => !approvedProducts.some((p) => p.name === n)
      );
      if (invalid.length) {
        const invalidNames = invalid.join("、");
        showToast(`选择的商品「${invalidNames}」不存在或已下架，请重新选择可用的商品`, "warning");
        return false;
      }
      
      // 检查商品是否存在于productData中但未核准
      const unapprovedProducts = selected.filter((name) => {
        const product = productData.find((p) => p.name === name);
        return product && product.status !== "approved";
      });
      if (unapprovedProducts.length) {
        const unapprovedNames = unapprovedProducts.join("、");
        showToast(`选择的商品「${unapprovedNames}」尚未核准，请等待商品审核通过后再创建服务`, "warning");
        return false;
      }
      const regions = regionsValue
        ? regionsValue
            .split(/[、,，]/)
            .map((s) => s.trim())
            .filter(Boolean)
        : [];
      const newSvc = {
        id: `SRV-${Date.now()}`,
        name,
        type,
        price,
        regions,
        products: selected,
        status: "pending",
        description:
          document.getElementById("service-new-description")?.value.trim() ||
          "",
        category: "",
        contract: "",
        contact: "",
        audits: [
          {
            time: new Date().toISOString().slice(0, 10),
            result: "等待平台审核",
          },
        ],
        updatedAt: formatDateTime(),
      };
      serviceData.unshift(newSvc);
      showToast("已提交服务创建申请，等待审核", "success");
      refreshServiceTable();
    },
  });
}

function openServiceDeleteDialog(id) {
  const svc = findServiceById(id);
  if (!svc) return;
  if (svc.status === "active") {
    showToast("生效中的服务不允许直接删除，请先下线/禁用后再试", "warning");
    return;
  }
  openModal({
    title: `删除服务 · ${svc.id}`,
    body: `<p>确认删除该服务？删除后不可恢复。</p><p class="modal-section__minor">提示：审核记录将一并移除（原型模拟）。</p>`,
    confirmText: "删除",
    onConfirm: () => {
      const idx = serviceData.findIndex((x) => x.id === svc.id);
      if (idx >= 0) serviceData.splice(idx, 1);
      showToast("已删除服务", "success");
      refreshServiceTable();
    },
  });
}

function renderProviderTable() {
  if (!els.providerTable) return;
  const keyword = (state.providerKeyword || "").toLowerCase();
  const type = state.providerType || "all";
  const region = (state.providerRegion || "").toLowerCase();

  const filtered = providerData.filter((item) => {
    const matchKeyword = keyword
      ? [item.name, item.contact].join(" ").toLowerCase().includes(keyword)
      : true;
    const matchType =
      type === "all" || item.types.includes(type.replace("广联", ""));
    const matchRegion = region
      ? item.region.toLowerCase().includes(region)
      : true;
    return matchKeyword && matchType && matchRegion;
  });

  if (!filtered.length) {
    els.providerTable.innerHTML = "";
    if (els.providerEmpty) els.providerEmpty.classList.remove("hidden");
  } else {
    if (els.providerEmpty) els.providerEmpty.classList.add("hidden");
    els.providerTable.innerHTML = filtered
      .map(
        (item) => `
          <tr>
            <td>${item.name}</td>
            <td>${item.types}</td>
            <td>${item.region}</td>
            <td>${item.contact}</td>
            <td>${item.status}</td>
            <td class="table-actions">
              <button class="btn btn--ghost" data-action="provider-detail" data-id="${item.id}">详情</button>
              <button class="btn btn--ghost" data-action="provider-eval" data-id="${item.id}">评估</button>
            </td>
          </tr>`
      )
      .join("");
  }
}

function renderContractTable() {
  if (!els.contractTable) return;
  const filtered = contractData;
  if (!filtered.length) {
    els.contractTable.innerHTML = "";
    if (els.contractEmpty) els.contractEmpty.classList.remove("hidden");
    return;
  }
  if (els.contractEmpty) els.contractEmpty.classList.add("hidden");

  els.contractTable.innerHTML = filtered
    .map(
      (item) => `
        <tr>
          <td>${item.id}</td>
          <td>${item.provider}</td>
          <td>${item.service}</td>
          <td>${item.region}</td>
          <td>${item.effectDate} - ${item.expireDate}</td>
          <td><span class="status-tag status-tag--${
            (CONTRACT_STATUS_META[item.statusCode || item.status] || {}).tone ||
            "info"
          }">${
        (CONTRACT_STATUS_META[item.statusCode || item.status] || {}).label ||
        item.status
      }</span></td>
          <td class="table-actions">
            <button class="btn btn--ghost" data-action="contract-detail" data-id="${
              item.id
            }">详情</button>
            <button class="btn btn--ghost" data-action="contract-operate" data-id="${
              item.id
            }">操作</button>
          </td>
        </tr>`
    )
    .join("");
}

function refreshPartnerView() {
  if (state.route === "partner") {
    renderPartner();
  }
}

function refreshActivityView() {
  if (state.route === "activity") {
    renderActivity();
  }
}

const PROVIDER_STATUS_OPTIONS = [
  { value: "合作中", label: "合作中" },
  { value: "待考察", label: "待考察" },
  { value: "已冻结", label: "已冻结" },
];

const PROVIDER_RATING_OPTIONS = ["S", "A", "B", "C"];

function openProviderDetail(id) {
  const provider = findProviderById(id);
  if (!provider) return;
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">基本信息</div>
      <div>类型：${provider.types}</div>
      <div>区域：${provider.region}</div>
      <div>联系人：${provider.contact}</div>
      <div>评级：${provider.rating || "未评定"}</div>
      <div class="modal-section__minor">加入时间：${
        provider.joinedAt || "—"
      } · 最近更新：${provider.updatedAt || "—"}</div>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">可提供服务</div>
      <ul class="modal-list">
        ${
          (provider.services || [])
            .map((item) => `<li>• ${item}</li>`)
            .join("") || "<li>• 暂无记录</li>"
        }
      </ul>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">近期表现</div>
      <ul class="modal-list">${
        (provider.recentCases || [])
          .map((item) => `<li>• ${item}</li>`)
          .join("") || "<li>• 暂无记录</li>"
      }</ul>
    </div>
  `;
  openModal({
    title: `服务商详情 · ${provider.name}`,
    body,
    confirmText: "关闭",
    cancelText: " ",
    onConfirm: () => {},
  });
}

function openProviderEvaluation(id) {
  const provider = findProviderById(id);
  if (!provider) return;
  const statusOptions = PROVIDER_STATUS_OPTIONS.map(
    (opt) =>
      `<option value="${opt.value}" ${
        provider.status === opt.value ? "selected" : ""
      }>${opt.label}</option>`
  ).join("");
  const ratingOptions = PROVIDER_RATING_OPTIONS.map(
    (rating) =>
      `<option value="${rating}" ${
        provider.rating === rating ? "selected" : ""
      }>${rating}</option>`
  ).join("");
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">评估结果</div>
      <label class="form-field">
        <span>合作评级</span>
        <select id="provider-eval-rating">${ratingOptions}</select>
      </label>
      <label class="form-field">
        <span>合作状态</span>
        <select id="provider-eval-status">${statusOptions}</select>
      </label>
      <label class="form-field">
        <span>评估备注 *</span>
        <textarea id="provider-eval-remark" rows="3" placeholder="例如通过考察，具备安装与维修能力"></textarea>
      </label>
    </div>
  `;
  openModal({
    title: `服务商评估 · ${provider.name}`,
    body,
    confirmText: "提交评估",
    onConfirm: () => {
      const remark = document
        .getElementById("provider-eval-remark")
        ?.value.trim();
      if (!remark) {
        showToast("请填写评估备注", "warning");
        return false;
      }
      const nextRating =
        document.getElementById("provider-eval-rating")?.value ||
        provider.rating;
      const nextStatus =
        document.getElementById("provider-eval-status")?.value ||
        provider.status;
      provider.rating = nextRating;
      provider.status = nextStatus;
      provider.updatedAt = formatDateTime();
      provider.recentCases = [
        remark,
        ...(provider.recentCases || []).slice(0, 4),
      ];
      showToast(`已更新服务商 ${provider.name} 的评估结果`, "success");
      refreshPartnerView();
    },
  });
}

function openContractDetail(id) {
  const contract = findContractById(id);
  if (!contract) return;
  const meta =
    CONTRACT_STATUS_META[contract.statusCode || contract.status] || {};
  const timelineHtml =
    (contract.timeline || [])
      .map((item) => `<li>• ${item.time} · ${item.event}</li>`)
      .join("") || "<li>• 暂无记录</li>";
  const termsHtml =
    (contract.terms || []).map((term) => `<li>• ${term}</li>`).join("") ||
    "<li>• 暂无条款</li>";
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">合同概览</div>
      <div>服务商：${contract.provider}</div>
      <div>服务：${contract.service}</div>
      <div>覆盖区域：${contract.region}</div>
      <div>状态：<span class="status-tag status-tag--${meta.tone || "info"}">${
    meta.label || contract.status
  }</span></div>
      <div class="modal-section__minor">有效期：${contract.effectDate} ~ ${
    contract.expireDate
  }</div>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">合作范围</div>
      <p>${contract.scope || "—"}</p>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">关键条款</div>
      <ul class="modal-list">${termsHtml}</ul>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">时间线</div>
      <ul class="modal-list">${timelineHtml}</ul>
    </div>
  `;
  openModal({
    title: `合同详情 · ${contract.id}`,
    body,
    confirmText: "关闭",
    cancelText: " ",
    onConfirm: () => {},
  });
}

function openContractCreateForm() {
  const providerOptions = providerData
    .map((item) => `<option value="${item.name}">${item.name}</option>`)
    .join("");
  const serviceOptions = serviceData
    .map((item) => `<option value="${item.name}">${item.name}</option>`)
    .join("");
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">合作信息</div>
      <label class="form-field">
        <span>服务商 *</span>
        <select id="contract-form-provider">${providerOptions}</select>
      </label>
      <label class="form-field">
        <span>关联服务（可多选）*</span>
        <select id="contract-form-service" multiple size="6">${serviceOptions}</select>
      </label>
      <label class="form-field">
        <span>适用区域 *</span>
        <input type="text" id="contract-form-region" placeholder="例如：上海、苏州" />
      </label>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">有效期</div>
      <label class="form-field">
        <span>生效日期 *</span>
        <input type="date" id="contract-form-effect" />
      </label>
      <label class="form-field">
        <span>到期日期 *</span>
        <input type="date" id="contract-form-expire" />
      </label>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">合作范围</div>
      <textarea id="contract-form-scope" rows="3" placeholder="请输入核心合作内容（选填）"></textarea>
    </div>
  `;
  openModal({
    title: "创建服务合同",
    body,
    confirmText: "提交审核",
    onConfirm: () => {
      const provider = document.getElementById("contract-form-provider")?.value;
      const serviceEl = document.getElementById("contract-form-service");
      const services = Array.from(serviceEl?.selectedOptions || []).map(
        (o) => o.value
      );
      const region = document
        .getElementById("contract-form-region")
        ?.value.trim();
      const effectDate = document.getElementById("contract-form-effect")?.value;
      const expireDate = document.getElementById("contract-form-expire")?.value;
      if (
        !provider ||
        !services.length ||
        !region ||
        !effectDate ||
        !expireDate
      ) {
        showToast("请补全合同的必填信息（至少选择一个服务）", "warning");
        return false;
      }
      const scopeVal =
        document.getElementById("contract-form-scope")?.value.trim() || "";
      let created = 0;
      services.forEach((svc, idx) => {
        const contractId = `CTR-${Date.now()}${
          services.length > 1 ? "-" + (idx + 1) : ""
        }`;
        contractData.unshift({
          id: contractId,
          provider,
          service: svc,
          region,
          effectDate,
          expireDate,
          status: "pending",
          statusCode: "pending",
          scope: scopeVal,
          terms: [],
          // 新增：双方确认机制
          pendingParty: "provider", // 当前等待哪一方确认：merchant(商户) 或 provider(服务商)
          merchantConfirmed: true, // 商户已确认（商户创建即确认）
          providerConfirmed: false, // 服务商未确认
          timeline: [
            { time: formatDateTime(), event: "商户发起合同申请并确认，等待服务商确认" },
          ],
          updatedAt: formatDateTime(),
        });
        created++;
      });
      showToast(
        created > 1 ? `已提交 ${created} 份合同申请` : "已提交合同申请",
        "success"
      );
      refreshContractTable();
    },
  });
}

function openContractOperate(id) {
  const contract = findContractById(id);
  if (!contract) return;
  const status = contract.statusCode || contract.status;
  let operations = [];
  if (status === "pending") {
    operations = [
      { value: "confirm", label: "确认生效" },
      { value: "cancel", label: "取消合同" },
    ];
  } else if (status === "active") {
    operations = [
      { value: "pause", label: "暂停履约" },
      { value: "cancel", label: "终止合同" },
    ];
  } else if (status === "paused") {
    operations = [
      { value: "activate", label: "恢复履约" },
      { value: "cancel", label: "终止合同" },
    ];
  }

  if (!operations.length) {
    showToast("当前状态不支持更多操作", "info");
    return;
  }

  const optionsHtml = operations
    .map(
      (op, index) => `
        <label class="form-field">
          <span>
            <input type="radio" name="contract-operate-action" value="${
              op.value
            }" ${index === 0 ? "checked" : ""} />
            ${op.label}
          </span>
        </label>`
    )
    .join("");
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">操作选项</div>
      ${optionsHtml}
      <label class="form-field">
        <span>备注</span>
        <textarea id="contract-operate-remark" rows="3" placeholder="补充说明（选填）"></textarea>
      </label>
    </div>
  `;
  openModal({
    title: `合同操作 · ${contract.id}`,
    body,
    confirmText: "执行操作",
    onConfirm: () => {
      const action = document.querySelector(
        "input[name='contract-operate-action']:checked"
      )?.value;
      if (!action) {
        showToast("请选择要执行的操作", "warning");
        return false;
      }
      const remark = document
        .getElementById("contract-operate-remark")
        ?.value.trim();
      let toastMessage = "";
      if (action === "confirm") {
        contract.statusCode = "active";
        contract.status = "active";
        appendContractTimeline(contract, "合同已确认生效");
        appendContractTimeline(contract, "已通知服务商");
        toastMessage = "合同已确认生效";
      } else if (action === "cancel") {
        contract.statusCode = "cancelled";
        contract.status = "cancelled";
        appendContractTimeline(contract, "合同已终止");
        appendContractTimeline(contract, "已通知服务商");
        contract.expireDate =
          contract.expireDate || formatDateTime().split(" ")[0];
        toastMessage = "合同已终止";
      } else if (action === "pause") {
        contract.statusCode = "paused";
        contract.status = "paused";
        appendContractTimeline(contract, "合同已暂停履约");
        appendContractTimeline(contract, "已通知服务商");
        toastMessage = "合同已暂停履约";
      } else if (action === "activate") {
        contract.statusCode = "active";
        contract.status = "active";
        appendContractTimeline(contract, "合同已恢复履约");
        appendContractTimeline(contract, "已通知服务商");
        toastMessage = "合同已恢复履约";
      }
      if (remark) {
        appendContractTimeline(contract, `备注：${remark}`);
      }
      contract.updatedAt = formatDateTime();
      showToast(toastMessage, "success");
      refreshContractTable();
    },
  });
}

function renderActivity() {
  activateTab("activity", state.tabs.activity);
  renderPromoTable();
  renderGroupTable();
  renderAssignLists();
}

function renderPromoTable() {
  if (!els.promoTable) return;
  const keyword = (state.promoKeyword || "").toLowerCase();
  const status = state.promoStatus || "all";
  const startFilter = state.promoStart ? new Date(state.promoStart) : null;
  const endFilter = state.promoEnd ? new Date(state.promoEnd) : null;
  const productKw = (state.promoProduct || "").toLowerCase();

  const filtered = promoData.filter((item) => {
    const matchKeyword = keyword
      ? [item.name, item.type].join(" ").toLowerCase().includes(keyword)
      : true;
    const matchStatus =
      status === "all" || (item.statusCode || item.status) === status;
    const s = item.start ? new Date(item.start) : null;
    const e = item.end ? new Date(item.end) : null;
    const matchDate =
      (!startFilter || (e && e >= startFilter)) &&
      (!endFilter || (s && s <= endFilter));
    const assigned = activityAssignments[item.id] || item.products || [];
    const matchProduct = productKw
      ? assigned.some(
          (pid) =>
            String(pid).toLowerCase().includes(productKw) ||
            getProductDisplayName(pid).toLowerCase().includes(productKw)
        )
      : true;
    return matchKeyword && matchStatus && matchDate && matchProduct;
  });

  if (!filtered.length) {
    els.promoTable.innerHTML = "";
    if (els.promoEmpty) els.promoEmpty.classList.remove("hidden");
    return;
  }
  if (els.promoEmpty) els.promoEmpty.classList.add("hidden");

  els.promoTable.innerHTML = filtered
    .map(
      (item) => `
        <tr>
          <td>${item.name}</td>
          <td>${item.type}</td>
          <td>${item.rule}</td>
          <td>${formatDateRange(item.start, item.end)}</td>
          <td><span class="status-tag status-tag--${
            (PROMO_STATUS_META[item.statusCode || item.status] || {}).tone ||
            "info"
          }">${
        (PROMO_STATUS_META[item.statusCode || item.status] || {}).label ||
        item.status
      }</span></td>
          <td class="table-actions">
            <button class="btn btn--ghost" data-action="promo-detail" data-id="${
              item.id
            }">详情</button>
            <button class="btn btn--ghost" data-action="activity-unlink" data-id="${
              item.id
            }">管理关联</button>
            <button class="btn btn--ghost" data-action="promo-stop" data-id="${
              item.id
            }">停止</button>
          </td>
        </tr>`
    )
    .join("");
}

function renderGroupTable() {
  if (!els.groupTable) return;
  const keyword = (state.groupKeyword || "").toLowerCase();
  const startFilter = state.groupStart ? new Date(state.groupStart) : null;
  const endFilter = state.groupEnd ? new Date(state.groupEnd) : null;

  const filtered = groupData.filter((item) => {
    const matchKeyword = keyword
      ? [item.name, String(item.membersRequired), String(item.price)]
          .join(" ")
          .toLowerCase()
          .includes(keyword)
      : true;
    const s = item.start ? new Date(item.start) : null;
    const e = item.end ? new Date(item.end) : null;
    const matchDate =
      (!startFilter || (e && e >= startFilter)) &&
      (!endFilter || (s && s <= endFilter));
    return matchKeyword && matchDate;
  });

  if (!filtered.length) {
    els.groupTable.innerHTML = "";
    if (els.groupEmpty) els.groupEmpty.classList.remove("hidden");
    return;
  }
  if (els.groupEmpty) els.groupEmpty.classList.add("hidden");

  els.groupTable.innerHTML = filtered
    .map(
      (item) => `
        <tr>
          <td>${item.name}</td>
          <td>成团人数 ${item.membersRequired} 人</td>
          <td>${formatDateRange(item.start, item.end)}</td>
          <td>${item.price}</td>
          <td><span class="status-tag status-tag--${
            (GROUP_STATUS_META[item.statusCode || item.status] || {}).tone ||
            "info"
          }">${
        (GROUP_STATUS_META[item.statusCode || item.status] || {}).label ||
        item.status
      }</span></td>
          <td class="table-actions">
            <button class="btn btn--ghost" data-action="group-detail" data-id="${
              item.id
            }">详情</button>
            <button class="btn btn--ghost" data-action="activity-unlink" data-id="${
              item.id
            }">管理关联</button>
            <button class="btn btn--ghost" data-action="group-stop" data-id="${
              item.id
            }">终止</button>
          </td>
        </tr>`
    )
    .join("");
}

function renderAssignLists() {
  if (els.assignActivityList) {
    els.assignActivityList.innerHTML = assignActivities
      .map(
        (item) => `
          <li class="list__item">
            <div class="list__meta">
              <span>${item.name}</span>
              <span>${item.type} · ${item.window}${
          activityAssignments[item.id]
            ? ` · 已关联 ${activityAssignments[item.id].length} 款商品`
            : ""
        }</span>
            </div>
            <div class="table-actions">
              <button class="btn ${
                state.assign.activityId === item.id
                  ? "btn--primary"
                  : "btn--ghost"
              }" data-action="assign-activity" data-id="${item.id}">${
          state.assign.activityId === item.id ? "已选择" : "选择"
        }</button>
            </div>
          </li>`
      )
      .join("");
  }

  if (els.assignProductList) {
    els.assignProductList.innerHTML = assignProducts
      .map((item) => {
        const selected = state.assign.productIds.includes(item.id);
        return `
          <li class="list__item">
            <span>${item.name}</span>
            <div class="table-actions">
              <button class="btn ${
                selected ? "btn--secondary" : "btn--ghost"
              }" data-action="assign-product" data-id="${item.id}">${
          selected ? "移除" : "加入"
        }</button>
            </div>
          </li>`;
      })
      .join("");
  }
}

function getActivityWindow(start, end) {
  if (!start || !end) return "";
  return `${start.slice(5)}-${end.slice(5)}`;
}

function upsertAssignActivity(id, name, type, start, end) {
  const window = getActivityWindow(start, end);
  const existing = assignActivities.find((item) => item.id === id);
  if (existing) {
    existing.name = name;
    existing.type = type;
    existing.window = window;
  } else {
    assignActivities.unshift({
      id,
      name,
      type,
      window,
    });
  }
}

function parseListInput(value = "") {
  return value
    .split(/[、,，\s]+/)
    .map((item) => item.trim())
    .filter(Boolean);
}

function openPromoDetail(id) {
  const promo = promoData.find((item) => item.id === id);
  if (!promo) return;
  const meta = PROMO_STATUS_META[promo.statusCode || promo.status] || {};
  const products =
    (promo.products || [])
      .map((sku) => `<li>• ${getProductDisplayName(sku)}</li>`)
      .join("") || "<li>• 暂无指定商品</li>";
  const timeline =
    (promo.timeline || [])
      .map((item) => `<li>• ${item.time} · ${item.event}</li>`)
      .join("") || "<li>• 暂无记录</li>";
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">活动概览</div>
      <div>类型：${promo.type}</div>
      <div>折扣规则：${promo.rule}</div>
      <div>渠道：${promo.channel || "全渠道"}</div>
      <div>状态：<span class="status-tag status-tag--${meta.tone || "info"}">${
    meta.label || promo.status
  }</span></div>
      <div class="modal-section__minor">活动时间：${formatDateRange(
        promo.start,
        promo.end
      )}</div>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">活动说明</div>
      <p>${promo.description || "暂无说明"}</p>
      ${
        promo.budget
          ? `<p class="modal-section__minor">预算：${promo.budget}</p>`
          : ""
      }
    </div>
    <div class="modal-section">
      <div class="modal-section__title">包含商品</div>
      <ul class="modal-list">${products}</ul>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">时间线</div>
      <ul class="modal-list">${timeline}</ul>
    </div>
  `;
  openModal({
    title: `促销详情 · ${promo.name}`,
    body,
    confirmText: "关闭",
    cancelText: " ",
    onConfirm: () => {},
  });
}

function openGroupStopDialog(id) {
  const group = groupData.find((item) => item.id === id);
  if (!group) return;
  if (
    (group.statusCode || group.status) === "finished" ||
    (group.statusCode || group.status) === "ended"
  ) {
    showToast("活动已结束，无需重复操作", "info");
    return;
  }
  openModal({
    title: "终止团购活动",
    body: `<p>确认立即结束团购 <strong>${group.name}</strong> 吗？结束后不可再开团。</p>`,
    confirmText: "确认结束",
    onConfirm: () => {
      setGroupStatus(group, "finished");
      group.updatedAt = formatDateTime();
      group.timeline = [
        ...(group.timeline || []),
        { time: formatDateTime(), event: "活动已手动结束" },
      ];
      showToast(`团购 ${group.name} 已结束`, "success");
      refreshActivityView();
    },
  });
}

function openActivityUnlinkForm(activityId) {
  const promo = promoData.find((it) => it.id === activityId);
  const group = groupData.find((it) => it.id === activityId);
  const activity = promo || group;
  if (!activity) return;
  const typeLabel = promo ? "促销" : "团购";
  const assigned = [
    ...(activityAssignments[activityId] || activity.products || []),
  ];
  if (!assigned.length) {
    showToast("当前活动未关联任何商品", "info");
    return;
  }
  const listHtml = assigned
    .map(
      (sku) => `<label class="checkbox">
        <input type="checkbox" name="unlinkSku" value="${sku}" />
        <span>${getProductDisplayName(sku)}</span>
      </label>`
    )
    .join("");
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">${typeLabel} · ${activity.name}</div>
      <p class="modal-section__minor">请选择要解除关联的商品（不会删除活动，仅解除与所选商品的关系）。</p>
      <div class="checkbox-group">${listHtml}</div>
    </div>`;
  openModal({
    title: "管理活动关联商品",
    body,
    confirmText: "解除关联",
    onConfirm: () => {
      const checked = Array.from(
        els.modalBody.querySelectorAll('input[name="unlinkSku"]:checked')
      ).map((el) => el.value);
      if (!checked.length) {
        showToast("请至少选择 1 个商品", "warning");
        return false;
      }
      const next = assigned.filter((sku) => !checked.includes(String(sku)));
      activityAssignments[activityId] = next;
      if (Array.isArray(activity.products)) activity.products = [...next];
      activity.updatedAt = formatDateTime();
      activity.timeline = [
        ...(activity.timeline || []),
        { time: formatDateTime(), event: `解除关联 ${checked.length} 款商品` },
      ];
      showToast(`已解除关联 ${checked.length} 款商品`, "success");
      refreshActivityView();
    },
  });
}

function openPromoStopDialog(id) {
  const promo = promoData.find((item) => item.id === id);
  if (!promo) return;
  if ((promo.statusCode || promo.status) === "finished") {
    showToast("活动已结束，无需重复操作", "info");
    return;
  }
  openModal({
    title: "终止促销活动",
    body: `<p>确认立即结束活动 <strong>${promo.name}</strong> 吗？结束后用户将无法再领取或参与。</p>`,
    confirmText: "确认结束",
    onConfirm: () => {
      setPromoStatus(promo, "finished");
      promo.updatedAt = formatDateTime();
      promo.timeline = [
        ...(promo.timeline || []),
        { time: formatDateTime(), event: "活动已手动结束" },
      ];
      showToast(`活动 ${promo.name} 已结束`, "success");
      refreshActivityView();
    },
  });
}

function openGroupDetail(id) {
  const group = groupData.find((item) => item.id === id);
  if (!group) return;
  const meta = GROUP_STATUS_META[group.statusCode || group.status] || {};
  const timeline =
    (group.timeline || [])
      .map((item) => `<li>• ${item.time} · ${item.event}</li>`)
      .join("") || "<li>• 暂无记录</li>";
  const products =
    (group.products || [])
      .map((sku) => `<li>• ${getProductDisplayName(sku)}</li>`)
      .join("") || "<li>• 暂无指定商品</li>";
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">活动概览</div>
      <div>团购价：${group.price}</div>
      <div>成团人数：${group.membersRequired} 人</div>
      <div>状态：<span class="status-tag status-tag--${meta.tone || "info"}">${
    meta.label || group.status
  }</span></div>
      <div class="modal-section__minor">活动时间：${formatDateRange(
        group.start,
        group.end
      )}</div>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">活动说明</div>
      <p>${group.description || "暂无说明"}</p>
      <p class="modal-section__minor">累计成团：${
        group.successCount || 0
      } 团</p>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">覆盖商品</div>
      <ul class="modal-list">${products}</ul>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">时间线</div>
      <ul class="modal-list">${timeline}</ul>
    </div>
  `;
  openModal({
    title: `团购详情 · ${group.name}`,
    body,
    confirmText: "关闭",
    cancelText: " ",
    onConfirm: () => {},
  });
}

function openActivityTemplateGuide() {
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">模板使用说明</div>
      <ul class="modal-list">
        <li>• 模板包含促销、团购两种活动示例，请根据需求填写字段。</li>
        <li>• 促销需提供活动名称、类型、折扣规则、起止时间、涉及商品。</li>
        <li>• 团购需提供团购价、成团人数、起止日期、配送与发货策略。</li>
        <li>• 填写完成后，可在“新建活动”弹窗中选择“从模板导入”。</li>
      </ul>
    </div>
  `;
  openModal({
    title: "活动模板说明",
    body,
    confirmText: "知道了",
    cancelText: " ",
    onConfirm: () => {},
  });
}

function openActivityCreateForm() {
  if (!state.isAdmin) {
    showToast("仅管理员可创建活动", "warning");
    return;
  }
  const body = `
    <div class="modal-section">
      <div class="modal-section__title">基础信息</div>
      <label class="form-field">
        <span>活动类型 *</span>
        <select id="activity-form-type">
          <option value="promo">促销活动</option>
          <option value="group">团购活动</option>
        </select>
      </label>
      <label class="form-field">
        <span>活动名称 *</span>
        <input type="text" id="activity-form-name" placeholder="请输入活动名称" />
      </label>
      <label class="form-field">
        <span>活动说明</span>
        <textarea id="activity-form-desc" rows="3" placeholder="简要说明活动亮点"></textarea>
      </label>
    </div>
    <div class="modal-section">
      <div class="modal-section__title">时间与对象</div>
      <label class="form-field">
        <span>开始日期 *</span>
        <input type="date" id="activity-form-start" />
      </label>
      <label class="form-field">
        <span>结束日期 *</span>
        <input type="date" id="activity-form-end" />
      </label>
      <label class="form-field">
        <span>关联商品（SKU，以逗号分隔）</span>
        <input type="text" id="activity-form-products" placeholder="例如：SKU-88001, SKU-88003" />
      </label>
    </div>
    <div class="modal-section" id="activity-form-promo">
      <div class="modal-section__title">促销参数</div>
      <label class="form-field">
        <span>折扣规则</span>
        <input type="text" id="activity-form-rule" placeholder="例如：满 2 件 8 折" />
      </label>
      <label class="form-field">
        <span>渠道</span>
        <input type="text" id="activity-form-channel" placeholder="线上/线下" />
      </label>
      <label class="form-field">
        <span>预算</span>
        <input type="text" id="activity-form-budget" placeholder="例如：预算 5 万" />
      </label>
    </div>
    <div class="modal-section" id="activity-form-group">
      <div class="modal-section__title">团购参数</div>
      <label class="form-field">
        <span>团购价 (¥)</span>
        <input type="number" id="activity-form-group-price" min="0" step="0.01" />
      </label>
      <label class="form-field">
        <span>成团人数</span>
        <input type="number" id="activity-form-group-members" min="2" step="1" />
      </label>
    </div>
  `;
  openModal({
    title: "新建活动",
    body,
    confirmText: "创建",
    onConfirm: () => {
      const type =
        document.getElementById("activity-form-type")?.value || "promo";
      const name = document.getElementById("activity-form-name")?.value.trim();
      const desc = document.getElementById("activity-form-desc")?.value.trim();
      const start = document.getElementById("activity-form-start")?.value;
      const end = document.getElementById("activity-form-end")?.value;
      if (!name || !start || !end) {
        showToast("请填写活动名称与起止日期", "warning");
        return false;
      }
      const products = parseListInput(
        document.getElementById("activity-form-products")?.value
      );
      if (type === "promo") {
        const rule =
          document.getElementById("activity-form-rule")?.value.trim() || "无";
        const channel =
          document.getElementById("activity-form-channel")?.value.trim() ||
          "全渠道";
        const budget =
          document.getElementById("activity-form-budget")?.value.trim() || "";
        const promoId = `ACT-${Date.now()}`;
        const promo = {
          id: promoId,
          name,
          type:
            document.getElementById("activity-form-type")?.selectedOptions?.[0]
              ?.text || "促销活动",
          rule,
          start,
          end,
          products,
          channel,
          budget,
          description: desc,
          timeline: [
            { time: formatDateTime(), event: "创建促销活动，等待审核" },
          ],
          createdAt: formatDateTime(),
        };
        setPromoStatus(promo, "pending");
        promoData.unshift(promo);
        activityAssignments[promoId] = [...products];
        upsertAssignActivity(promoId, name, "促销", start, end);
        showToast(`促销活动 ${name} 已创建，等待审核`, "success");
      } else {
        const price = Number(
          document.getElementById("activity-form-group-price")?.value
        );
        const members = Number(
          document.getElementById("activity-form-group-members")?.value
        );
        if (Number.isNaN(price) || Number.isNaN(members) || members < 2) {
          showToast("请填写有效的团购价与成团人数", "warning");
          return false;
        }
        const groupId = `GRP-${Date.now()}`;
        const group = {
          id: groupId,
          name,
          membersRequired: members,
          start,
          end,
          price: `¥ ${price}`,
          description: desc,
          successCount: 0,
          timeline: [{ time: formatDateTime(), event: "提交团购活动等待上线" }],
          products,
          createdAt: formatDateTime(),
        };
        setGroupStatus(group, "scheduled");
        groupData.unshift(group);
        activityAssignments[groupId] = [...products];
        upsertAssignActivity(groupId, name, "团购", start, end);
        showToast(`团购活动 ${name} 已创建`, "success");
      }
      refreshActivityView();
    },
  });
}

function updateOrderStatus(orderId, nextStatus) {
  const order = orderData.find((item) => item.id === orderId);
  if (!order) return;
  order.status = nextStatus;
  showToast(`订单 ${orderId} 状态已更新`, "success");
  renderOrders();
}

function openOrderCancel(orderId) {
  const order = orderData.find((item) => item.id === orderId);
  if (!order) return;
  openModal({
    title: "取消订单",
    body: `<p>确认取消订单 <strong>${orderId}</strong> 吗？已支付金额将自动进入退款流程。</p>`,
    confirmText: "确认取消",
    onConfirm: () => {
      // 仅允许未支付/待接受/待发货订单取消
      const cancellable = ["unpaid", "awaiting_accept", "awaiting_ship"];
      if (!cancellable.includes(order.status)) {
        showToast("当前状态不可取消", "warning");
        return false;
      }
      order.status = "cancelled";
      order.timeline = [
        ...(order.timeline || []),
        "商户取消订单，系统已发起退款并取消运单",
      ];
      // 触发退款子流程（原型中仅记录日志）
      refundData.unshift({
        id: `REF-${Date.now()}`,
        paymentId:
          (paymentData.find((p) => p.order === order.id) || {}).id || "",
        time: formatDateTime(),
        amount:
          (paymentData.find((p) => p.order === order.id) || {}).amount || "",
        share: "待退分账",
      });
      showToast(`订单 ${orderId} 已取消并触发退款`, "success");
      renderOrders();
      renderFinance();
    },
  });
}

function showToast(message, type = "info") {
  if (!els.toastContainer) return;
  const toast = document.createElement("div");
  toast.className = `toast toast--${type}`;
  toast.innerHTML = `<span>${message}</span><button class="btn btn--ghost" aria-label="关闭提醒">关闭</button>`;
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
  if (!els.modal) return;
  els.modalTitle.textContent = title;
  els.modalBody.innerHTML = body;
  els.modalConfirm.textContent = confirmText;
  els.modalCancel.textContent = cancelText;
  els.modal.classList.add("active");
  els.modalConfirm._handler = onConfirm;
}

function closeModal() {
  if (!els.modal) return;
  els.modal.classList.remove("active");
  els.modalBody.innerHTML = "";
  els.modalConfirm._handler = null;
}

document.addEventListener("click", (event) => {
  const actionBtn = event.target.closest("[data-action]");
  if (!actionBtn) return;
  const action = actionBtn.dataset.action;
  switch (action) {
    case "assign-activity":
      state.assign.activityId = actionBtn.dataset.id;
      state.assign.productIds = [
        ...(activityAssignments[state.assign.activityId] || []),
      ];
      renderAssignLists();
      showToast("已选择活动，继续选择商品", "info");
      break;
    case "assign-product":
      toggleAssignProduct(actionBtn.dataset.id);
      break;
    case "staff-suspend":
      confirmStaffStatusChange(actionBtn.dataset.id, "suspended");
      break;
    case "staff-resume":
      confirmStaffStatusChange(actionBtn.dataset.id, "active");
      break;
    case "staff-delete":
      confirmStaffDeletion(actionBtn.dataset.id);
      break;
    case "promo-stop":
      openPromoStopDialog(actionBtn.dataset.id);
      break;
    case "promo-detail":
      openPromoDetail(actionBtn.dataset.id);
      break;
    case "group-detail":
      openGroupDetail(actionBtn.dataset.id);
      break;
    case "group-export":
      showToast("团购数据导出完成", "success");
      break;
    default:
      break;
  }
});

function toggleAssignProduct(id) {
  if (!state.assign.activityId) {
    showToast("请先选择活动", "warning");
    return;
  }
  const exists = state.assign.productIds.includes(id);
  state.assign.productIds = exists
    ? state.assign.productIds.filter((item) => item !== id)
    : [...state.assign.productIds, id];
  renderAssignLists();
}

document.addEventListener("DOMContentLoaded", init);
