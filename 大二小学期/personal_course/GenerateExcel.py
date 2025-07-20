import random
import pandas as pd
from datetime import datetime
import argparse
import os

'''
主要功能：
生成标准测试数据：

按指定数量生成正常的课程数据
包含所有必填和可选字段
随机分配必修/选修标签
生成错误测试数据：

课程名称为空
星期数字超出范围（8）
标签值错误（"核心"）
节次超出范围（15-16）
邮箱格式错误
生成格式错误文件：

表头名称不匹配
用于测试格式验证

课程数据生成使用方法
# 安装依赖
pip install pandas openpyxl

# 生成50条正常数据
python GenerateExcel.py

# 生成100条正常数据
python GenerateExcel.py -n 100

# 生成包含错误的测试文件
python GenerateExcel.py -t error

# 生成所有类型的测试文件
python GenerateExcel.py -t all

# 指定输出文件名
python GenerateExcel.py -n 200 -o my_test_courses

'''
# --- 1. 配置与数据池 ---

# 扩展的数据池，增加复杂性
COURSE_NAMES = [
    # 计算机类
    "软件工程", "数据结构与算法", "计算机网络", "操作系统原理", "数据库系统", "编译原理",
    "人工智能导论", "机器学习基础", "深度学习", "计算机视觉", "自然语言处理", "区块链技术",
    "网络安全", "信息安全", "密码学", "分布式系统", "云计算", "大数据技术",
    "Web开发技术", "移动应用开发", "游戏开发", "嵌入式系统", "物联网技术",
    
    # 数学类
    "高等数学A", "高等数学B", "线性代数", "概率论与数理统计", "离散数学", "数值分析",
    "运筹学", "数学建模", "复变函数", "实变函数", "泛函分析", "拓扑学",
    
    # 物理类
    "大学物理A", "大学物理B", "理论力学", "电磁学", "光学", "原子物理学", "量子力学",
    "热力学与统计物理", "固体物理", "激光原理",
    
    # 语言类
    "大学英语", "高级英语", "英语听说", "英语写作", "商务英语", "科技英语",
    "日语基础", "法语入门", "德语基础", "西班牙语",
    
    # 通识类
    "马克思主义基本原理", "毛泽东思想概论", "中国近现代史纲要", "思想道德修养",
    "形势与政策", "军事理论", "体育", "心理学导论", "哲学概论", "艺术欣赏",
    "经济学原理", "管理学基础", "会计学原理", "统计学", "市场营销"
]

TEACHERS = [
    # 中文姓名
    "张伟", "李静", "王英", "刘洋", "陈秀英", "赵强", "周敏", "黄磊", "吴涛", "徐明",
    "孙丽", "马超", "朱华", "胡军", "郭艳", "何鹏", "高峰", "林娜", "罗斌", "梁雪",
    "董建", "程亮", "石磊", "贾敏", "韩冰", "曹阳", "彭飞", "邓丽", "范伟", "田野",
    
    # 英文姓名（模拟外教）
    "John Smith", "Mary Johnson", "David Brown", "Sarah Davis", "Michael Wilson",
    "Lisa Anderson", "Robert Taylor", "Jennifer White", "William Garcia", "Amanda Lee"
]

LOCATIONS_BUILDINGS = [
    "学武楼", "西部片区二号楼", "西部片区四号楼", "益海嘉里楼", "坤乾楼", "文宣楼",
    "图书馆", "实验楼", "音乐厅", "体育馆", "艺术楼", "工程楼", "医学楼", "法学楼",
    "经管楼", "外语楼", "数学楼", "物理楼", "化学楼", "生物楼"
]

ROOM_NUMBERS = [
    "101", "102", "103", "104", "105", "201", "202", "203", "204", "205",
    "301", "302", "303", "304", "305", "401", "402", "403", "404", "405",
    "501", "502", "503", "504", "505", "A101", "A102", "A201", "A301",
    "B101", "B201", "B301", "C101", "C201", "实验室1", "实验室2", "多媒体教室"
]

EMAIL_DOMAINS = [
    "xmu.edu.cn", "example.com", "university.edu", "school.org", "college.edu",
    "gmail.com", "163.com", "qq.com", "hotmail.com", "sina.com"
]

GROUP_CHAT_PREFIXES = ["QQ群", "微信群", "钉钉群", "课程群"]

COURSE_TAGS = ["必修", "选修"]

NOTES = [
    "期末开卷考试", "期末闭卷考试", "无期末考试", "有随堂测试", "重点课程，请注意听讲",
    "需要做课程设计", "包含实验课", "双语教学", "全英文授课", "小班教学",
    "网络授课", "混合式教学", "翻转课堂", "案例教学", "项目导向",
    "考试占比70%", "平时成绩占比40%", "出勤率要求高", "需要预习", "课后作业较多",
    "", "无特殊要求"  # 空值和无要求
]

# --- 2. 辅助函数 ---

def generate_teacher_email(teacher_name):
    """根据教师姓名生成邮箱"""
    if any(ord(char) > 127 for char in teacher_name):  # 中文姓名
        # 简单拼音转换（实际应用中可以使用pypinyin）
        pinyin_map = {
            '张': 'zhang', '李': 'li', '王': 'wang', '刘': 'liu', '陈': 'chen',
            '赵': 'zhao', '周': 'zhou', '黄': 'huang', '吴': 'wu', '徐': 'xu',
            '孙': 'sun', '马': 'ma', '朱': 'zhu', '胡': 'hu', '郭': 'guo',
            '何': 'he', '高': 'gao', '林': 'lin', '罗': 'luo', '梁': 'liang',
            '董': 'dong', '程': 'cheng', '石': 'shi', '贾': 'jia', '韩': 'han',
            '曹': 'cao', '彭': 'peng', '邓': 'deng', '范': 'fan', '田': 'tian',
            '伟': 'wei', '静': 'jing', '英': 'ying', '洋': 'yang', '秀': 'xiu',
            '强': 'qiang', '敏': 'min', '磊': 'lei', '涛': 'tao', '明': 'ming',
            '丽': 'li', '超': 'chao', '华': 'hua', '军': 'jun', '艳': 'yan',
            '鹏': 'peng', '峰': 'feng', '娜': 'na', '斌': 'bin', '雪': 'xue',
            '建': 'jian', '亮': 'liang', '冰': 'bing', '阳': 'yang', '飞': 'fei',
            '野': 'ye'
        }
        
        pinyin_name = ""
        for char in teacher_name:
            pinyin_name += pinyin_map.get(char, char.lower())
        
        email_prefix = pinyin_name
    else:  # 英文姓名
        email_prefix = teacher_name.lower().replace(" ", ".")
    
    domain = random.choice(EMAIL_DOMAINS)
    return f"{email_prefix}@{domain}"

def generate_group_chat_id():
    """生成课程群号"""
    prefix = random.choice(GROUP_CHAT_PREFIXES)
    number = random.randint(100000000, 999999999)  # 9位数字
    return f"{prefix}{number}"

def should_generate_optional_field(probability=0.7):
    """按概率决定是否生成可选字段"""
    return random.random() < probability

# --- 3. 数据生成核心逻辑 ---

def generate_course_data(num_courses=50):
    """生成课程数据"""
    courses_data = []
    
    for i in range(num_courses):
        # 必填字段
        course_name = random.choice(COURSE_NAMES)
        day_of_week = random.randint(1, 7)
        start_period = random.randint(1, 10)
        end_period = random.randint(start_period, min(start_period + 3, 12))  # 最多4节课
        start_week = random.randint(1, 3)
        end_week = random.randint(max(start_week + 4, 8), 20)
        
        # 可选字段（按概率生成）
        teachers = []
        num_teachers = random.randint(1, 3)
        selected_teachers = random.sample(TEACHERS, num_teachers)
        teachers_str = ",".join(selected_teachers) if should_generate_optional_field(0.9) else ""
        
        main_teacher_email = ""
        if teachers_str and should_generate_optional_field(0.6):
            main_teacher = selected_teachers[0]
            main_teacher_email = generate_teacher_email(main_teacher)
        
        course_group_chat_id = ""
        if should_generate_optional_field(0.5):
            course_group_chat_id = generate_group_chat_id()
        
        tag = random.choice(COURSE_TAGS) if should_generate_optional_field(0.95) else "必修"
        
        location = ""
        if should_generate_optional_field(0.85):
            building = random.choice(LOCATIONS_BUILDINGS)
            room = random.choice(ROOM_NUMBERS)
            location = f"{building}-{room}"
        
        note = ""
        if should_generate_optional_field(0.4):
            note = random.choice([n for n in NOTES if n])  # 排除空字符串
        
        course_data = {
            "课程名称": course_name,
            "教师": teachers_str,
            "主讲老师邮箱": main_teacher_email,
            "课程群号": course_group_chat_id,
            "标签": tag,
            "上课地点": location,
            "星期": day_of_week,
            "开始节次": start_period,
            "结束节次": end_period,
            "开始周": start_week,
            "结束周": end_week,
            "备注": note
        }
        
        courses_data.append(course_data)
    
    return courses_data

def generate_test_data_with_errors(num_courses=20):
    """生成包含错误数据的测试文件"""
    courses_data = []
    
    for i in range(num_courses):
        if i == 2:  # 第3行：课程名称为空
            course_data = {
                "课程名称": "",
                "教师": "张老师",
                "主讲老师邮箱": "zhang@xmu.edu.cn",
                "课程群号": "QQ群123456789",
                "标签": "必修",
                "上课地点": "学武楼-101",
                "星期": 1,
                "开始节次": 1,
                "结束节次": 2,
                "开始周": 1,
                "结束周": 16,
                "备注": "测试空课程名称"
            }
        elif i == 4:  # 第5行：星期数字错误
            course_data = {
                "课程名称": "数据结构",
                "教师": "李老师",
                "主讲老师邮箱": "li@xmu.edu.cn",
                "课程群号": "",
                "标签": "必修",
                "上课地点": "实验楼-201",
                "星期": 8,  # 错误：应该是1-7
                "开始节次": 1,
                "结束节次": 2,
                "开始周": 1,
                "结束周": 16,
                "备注": "测试错误星期"
            }
        elif i == 6:  # 第7行：标签错误
            course_data = {
                "课程名称": "操作系统",
                "教师": "王老师",
                "主讲老师邮箱": "wang@xmu.edu.cn",
                "课程群号": "微信群987654321",
                "标签": "核心",  # 错误：应该是"必修"或"选修"
                "上课地点": "文宣楼-301",
                "星期": 3,
                "开始节次": 3,
                "结束节次": 4,
                "开始周": 1,
                "结束周": 16,
                "备注": "测试错误标签"
            }
        elif i == 8:  # 第9行：节次错误
            course_data = {
                "课程名称": "计算机网络",
                "教师": "赵老师",
                "主讲老师邮箱": "zhao@xmu.edu.cn",
                "课程群号": "",
                "标签": "必修",
                "上课地点": "坤乾楼-402",
                "星期": 5,
                "开始节次": 15,  # 错误：应该是1-12
                "结束节次": 16,  # 错误：应该是1-12
                "开始周": 1,
                "结束周": 16,
                "备注": "测试错误节次"
            }
        elif i == 10:  # 第11行：邮箱格式错误
            course_data = {
                "课程名称": "软件工程",
                "教师": "陈老师",
                "主讲老师邮箱": "invalid-email",  # 错误邮箱格式
                "课程群号": "QQ群555666777",
                "标签": "必修",
                "上课地点": "益海嘉里楼-501",
                "星期": 2,
                "开始节次": 5,
                "结束节次": 6,
                "开始周": 1,
                "结束周": 16,
                "备注": "测试错误邮箱"
            }
        else:  # 正常数据
            course_data = generate_course_data(1)[0]
        
        courses_data.append(course_data)
    
    return courses_data

def create_excel_file(courses_data, filename):
    """创建Excel文件"""
    # 创建DataFrame
    df = pd.DataFrame(courses_data)
    
    # 确保输出目录存在
    output_dir = "excel_test_files"
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)
    
    filepath = os.path.join(output_dir, filename)
    
    # 写入Excel文件
    with pd.ExcelWriter(filepath, engine='openpyxl') as writer:
        df.to_excel(writer, sheet_name='课程数据', index=False)
        
        # 获取工作表对象，设置列宽
        worksheet = writer.sheets['课程数据']
        
        # 设置列宽
        column_widths = {
            'A': 15,  # 课程名称
            'B': 20,  # 教师
            'C': 25,  # 主讲老师邮箱
            'D': 15,  # 课程群号
            'E': 8,   # 标签
            'F': 20,  # 上课地点
            'G': 8,   # 星期
            'H': 10,  # 开始节次
            'I': 10,  # 结束节次
            'J': 10,  # 开始周
            'K': 10,  # 结束周
            'L': 30   # 备注
        }
        
        for col, width in column_widths.items():
            worksheet.column_dimensions[col].width = width
    
    return filepath

def create_invalid_format_file():
    """创建格式错误的测试文件"""
    # 缺少必要表头的文件
    invalid_data = [
        {
            "课程名": "高等数学",  # 错误：应该是"课程名称"
            "老师": "张老师",     # 错误：应该是"教师"
            "地点": "学武楼-101", # 错误：应该是"上课地点"
            "周几": 1,           # 错误：应该是"星期"
            "开始节次": 1,
            "结束节次": 2,
            "开始周": 1,
            "结束周": 16
        }
    ]
    
    df = pd.DataFrame(invalid_data)
    output_dir = "excel_test_files"
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)
    
    filepath = os.path.join(output_dir, "invalid_format.xlsx")
    df.to_excel(filepath, index=False)
    return filepath

# --- 4. 主函数 ---

def main():
    parser = argparse.ArgumentParser(description='生成Excel课程数据文件用于测试导入功能')
    parser.add_argument('-n', '--num', type=int, default=50, help='生成课程数据的数量 (默认: 50)')
    parser.add_argument('-t', '--type', choices=['normal', 'error', 'invalid', 'all'], 
                       default='normal', help='生成文件类型 (默认: normal)')
    parser.add_argument('-o', '--output', type=str, help='输出文件名 (不包含扩展名)')
    
    args = parser.parse_args()
    
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    
    if args.type in ['normal', 'all']:
        # 生成正常数据文件
        print(f"正在生成 {args.num} 条正常课程数据...")
        normal_data = generate_course_data(args.num)
        
        filename = args.output if args.output else f"courses_normal_{args.num}_{timestamp}.xlsx"
        if not filename.endswith('.xlsx'):
            filename += '.xlsx'
            
        filepath = create_excel_file(normal_data, filename)
        print(f"✅ 正常数据文件已生成: {filepath}")
        
        # 显示统计信息
        df = pd.DataFrame(normal_data)
        required_count = df[df['标签'] == '必修'].shape[0]
        optional_count = df[df['标签'] == '选修'].shape[0]
        print(f"   - 必修课程: {required_count} 门")
        print(f"   - 选修课程: {optional_count} 门")
        print(f"   - 有教师信息: {df[df['教师'] != ''].shape[0]} 门")
        print(f"   - 有邮箱信息: {df[df['主讲老师邮箱'] != ''].shape[0]} 门")
        print(f"   - 有上课地点: {df[df['上课地点'] != ''].shape[0]} 门")
    
    if args.type in ['error', 'all']:
        # 生成包含错误的测试文件
        print(f"\n正在生成包含错误数据的测试文件...")
        error_data = generate_test_data_with_errors(20)
        
        error_filename = f"courses_with_errors_{timestamp}.xlsx"
        error_filepath = create_excel_file(error_data, error_filename)
        print(f"✅ 错误数据文件已生成: {error_filepath}")
        print(f"   - 包含5种常见错误类型，用于测试错误处理功能")
    
    if args.type in ['invalid', 'all']:
        # 生成格式错误的文件
        print(f"\n正在生成格式错误的测试文件...")
        invalid_filepath = create_invalid_format_file()
        print(f"✅ 格式错误文件已生成: {invalid_filepath}")
        print(f"   - 表头格式错误，用于测试格式验证功能")
    
    print(f"\n📁 所有文件已保存到: excel_test_files/ 目录")
    print(f"🔧 使用方法: python GenerateExcel.py -n 100 -t all")

if __name__ == "__main__":
    main()