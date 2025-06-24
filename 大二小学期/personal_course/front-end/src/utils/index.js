// src/utils/index.js

/**
 * 格式化日期和时间
 * @param {Date|string|number} date - 需要格式化的日期对象、字符串或时间戳
 * @param {string} fmt - 格式化字符串，如 'YYYY-mm-dd HH:MM:SS'
 * @returns {string} - 格式化后的字符串
 */
export function formatDate(date, fmt = 'YYYY-mm-dd HH:MM:SS') {
  if (!date) return ''
  
  const d = new Date(date)
  const o = {
    'm+': d.getMonth() + 1, // 月份
    'd+': d.getDate(), // 日
    'H+': d.getHours(), // 小时
    'M+': d.getMinutes(), // 分
    'S+': d.getSeconds(), // 秒
    'q+': Math.floor((d.getMonth() + 3) / 3), // 季度
    's': d.getMilliseconds() // 毫秒
  }

  if (/(Y+)/.test(fmt)) {
    fmt = fmt.replace(RegExp.$1, (d.getFullYear() + '').substr(4 - RegExp.$1.length))
  }

  for (let k in o) {
    if (new RegExp('(' + k + ')').test(fmt)) {
      fmt = fmt.replace(RegExp.$1, (RegExp.$1.length === 1) ? (o[k]) : (('00' + o[k]).substr(('' + o[k]).length)))
    }
  }
  return fmt
}
