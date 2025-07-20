import random
import datetime
import bcrypt
import argparse
'''
# 生成默认数据（14个用户，混合风格）
python Data.py

# 生成50个额外用户，中文风格
python Data.py -u 50 -s chinese

# 生成100个额外用户，英文风格，保存到文件
python Data.py -u 100 -s english -o test_data.sql

# 生成20个创意用户名
python Data.py -u 20 -s creative
'''
# --- 1. 配置与数据池 ---

# 密码 '123456' 的 Bcrypt 哈希值 (每次运行脚本值都不同，但都有效)
PASSWORD_RAW = '123456'
PASSWORD_HASH = bcrypt.hashpw(PASSWORD_RAW.encode('utf-8'), bcrypt.gensalt()).decode('utf-8')

# 新增：多样化的用户名池
CHINESE_SURNAMES = [
    "张", "李", "王", "刘", "陈", "杨", "黄", "赵", "周", "吴",
    "徐", "孙", "朱", "马", "胡", "郭", "林", "何", "高", "梁",
    "郑", "罗", "宋", "谢", "唐", "韩", "冯", "于", "董", "萧",
    "程", "曹", "袁", "邓", "许", "傅", "沈", "曾", "彭", "吕"
]

CHINESE_GIVEN_NAMES = [
    "晨", "阳", "雪", "华", "明", "静", "伟", "娜", "磊", "丽",
    "强", "敏", "涛", "艳", "超", "洋", "峰", "霞", "军", "燕",
    "辉", "萍", "鹏", "红", "斌", "玲", "勇", "芳", "杰", "梅",
    "宇", "琳", "飞", "莉", "刚", "倩", "浩", "婷", "凯", "欣",
    "博", "怡", "龙", "佳", "虎", "慧", "建", "兰", "文", "英"
]

ENGLISH_FIRST_NAMES = [
    "Alex", "Emma", "James", "Olivia", "William", "Sophia", "Benjamin", "Charlotte",
    "Lucas", "Amelia", "Henry", "Harper", "Alexander", "Evelyn", "Sebastian", "Abigail",
    "Jack", "Emily", "Owen", "Elizabeth", "Theodore", "Mila", "Jacob", "Ella",
    "Leo", "Avery", "Noah", "Sofia", "Oliver", "Camila", "Ethan", "Aria"
]

ENGLISH_LAST_NAMES = [
    "Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia", "Miller", "Davis",
    "Rodriguez", "Martinez", "Hernandez", "Lopez", "Gonzalez", "Wilson", "Anderson", "Thomas",
    "Taylor", "Moore", "Jackson", "Martin", "Lee", "Perez", "Thompson", "White",
    "Harris", "Sanchez", "Clark", "Ramirez", "Lewis", "Robinson", "Walker", "Young"
]

CREATIVE_USERNAMES = [
    "skywalker", "moonlight", "sunshine", "stargazer", "dreamcatcher", "nightowl",
    "firefly", "butterfly", "rainbow", "melody", "harmony", "symphony", "phoenix",
    "dragon", "tiger", "eagle", "wolf", "lion", "bear", "fox", "deer", "rabbit",
    "ocean", "river", "mountain", "forest", "garden", "flower", "tree", "leaf",
    "crystal", "diamond", "pearl", "jade", "ruby", "emerald", "sapphire", "gold",
    "silver", "copper", "iron", "steel", "thunder", "lightning", "storm", "wind"
]

# 扩展的数据池
TERM_NAMES = {
    "2023-2024秋季学期": ("2023-09-01", "2024-01-11"),
    "2023-2024春季学期": ("2024-02-25", "2024-06-14"),
    "2023-2024夏季学期": ("2024-06-15", "2024-08-20"),
    "2024-2025春季学期": ("2025-02-10", "2025-06-19"),
    "2024-2025夏季学期": ("2025-06-20", "2025-08-22"),
    "2024-2025秋季学期": ("2024-09-01", "2025-01-19"),
    "2025-2026春季学期": ("2026-02-16", "2026-06-22"),
    "2025-2026秋季学期": ("2025-09-08", "2026-01-16"),
    "2025-2026夏季学期": ("2026-06-23", "2026-08-28"),
}

# [其他数据池保持不变...]
LOCATIONS_BUILDINGS = [
    "学武楼", "西部片区二号楼", "西部片区四号楼", "益海嘉里楼", "坤乾楼", "文宣楼",
    "图书馆", "实验楼", "音乐厅", "体育馆", "艺术楼", "工程楼", "医学楼", "法学楼",
    "经管楼", "外语楼", "数学楼", "物理楼", "化学楼", "生物楼", "信息楼", "环境楼"
]

ROOM_NUMBERS = [
    "101", "102", "103", "104", "105", "201", "202", "203", "204", "205",
    "301", "302", "303", "304", "305", "401", "402", "403", "404", "405",
    "501", "502", "503", "504", "505", "A101", "A102", "A201", "A301",
    "B101", "B201", "B301", "C101", "C201", "实验室1", "实验室2", "多媒体教室",
    "阶梯教室1", "阶梯教室2", "小教室", "讨论室", "机房1", "机房2", "语音室"
]

# 扩展教师名单
TEACHERS = [
    # 中文教师
    "张伟", "李静", "王英", "刘洋", "陈秀英", "赵强", "周敏", "黄磊", "吴涛", "徐明",
    "孙丽", "马超", "朱华", "胡军", "郭艳", "何鹏", "高峰", "林娜", "罗斌", "梁雪",
    "董建华", "程亮", "石磊", "贾敏", "韩冰", "曹阳", "彭飞", "邓丽", "范伟", "田野",
    "蒋勇", "韦霞", "卢杰", "陆敏", "易鹏", "钱丽", "汪强", "于洋", "任峰", "廖雪",
    
    # 外教
    "John Smith", "Mary Johnson", "David Brown", "Sarah Davis", "Michael Wilson",
    "Lisa Anderson", "Robert Taylor", "Jennifer White", "William Garcia", "Amanda Lee",
    "James Miller", "Emily Clark", "Daniel Rodriguez", "Jessica Martinez", "Christopher Lewis"
]

# 大幅扩展课程名称
COURSE_NAMES = [
    # 计算机科学类
    "软件工程", "数据结构与算法", "计算机网络", "操作系统原理", "数据库系统", "编译原理",
    "人工智能导论", "机器学习基础", "深度学习", "计算机视觉", "自然语言处理", "区块链技术",
    "网络安全", "信息安全", "密码学", "分布式系统", "云计算技术", "大数据分析",
    "Web开发技术", "移动应用开发", "游戏开发基础", "嵌入式系统", "物联网技术", "虚拟现实技术",
    "计算机图形学", "数字图像处理", "模式识别", "算法设计与分析", "系统分析与设计",
    
    # 数学类
    "高等数学A", "高等数学B", "高等数学C", "线性代数", "概率论与数理统计", "离散数学",
    "数值分析", "运筹学", "数学建模", "复变函数与积分变换", "实变函数", "泛函分析",
    "拓扑学", "抽象代数", "数论", "微分几何", "偏微分方程", "随机过程",
    
    # 物理类
    "大学物理A", "大学物理B", "大学物理实验", "理论力学", "电磁学", "光学", "原子物理学",
    "量子力学", "热力学与统计物理", "固体物理", "激光原理", "近代物理实验",
    
    # 语言文学类
    "大学英语", "高级英语", "英语听说", "英语写作", "商务英语", "科技英语翻译",
    "日语基础", "日语会话", "法语入门", "德语基础", "西班牙语", "俄语基础",
    "古代汉语", "现代汉语", "中国古代文学", "中国现当代文学", "外国文学", "语言学概论",
    
    # 经济管理类
    "经济学原理", "微观经济学", "宏观经济学", "管理学基础", "会计学原理", "财务管理",
    "市场营销", "人力资源管理", "组织行为学", "战略管理", "运营管理", "项目管理",
    "国际贸易", "金融学", "统计学", "计量经济学", "商法", "税法",
    
    # 通识教育类
    "马克思主义基本原理", "毛泽东思想和中国特色社会主义理论体系概论", "中国近现代史纲要",
    "思想道德与法治", "形势与政策", "军事理论", "军事技能", "心理健康教育",
    "大学生职业规划", "创新创业基础", "体育", "美学原理", "艺术欣赏", "音乐鉴赏",
    "哲学概论", "逻辑学", "伦理学", "社会学概论", "政治学原理", "历史学概论"
]

# 新增邮箱域名
EMAIL_DOMAINS = [
    "xmu.edu.cn", "example.com", "university.edu", "school.org", "college.edu",
    "gmail.com", "163.com", "qq.com", "hotmail.com", "sina.com", "126.com",
    "yahoo.com", "outlook.com", "foxmail.com", "sohu.com"
]

# 新增课程群号前缀
GROUP_CHAT_PREFIXES = ["QQ群", "微信群", "钉钉群", "腾讯会议", "飞书群", "企业微信"]

# 新增更丰富的备注内容
COURSE_NOTES = [
    "期末开卷考试", "期末闭卷考试", "无期末考试，以课程论文替代", "有随堂测试", 
    "重点课程，请注意听讲", "需要做课程设计", "包含实验课", "双语教学", "全英文授课",
    "小班教学", "网络授课", "混合式教学", "翻转课堂", "案例教学", "项目导向教学",
    "考试占比70%，平时成绩30%", "平时成绩占比40%，期末60%", "出勤率要求较高",
    "需要预习相关材料", "课后作业较多", "有课程实习要求", "需要团队合作完成项目",
    "包含校外实践环节", "有企业导师参与", "采用PBL教学法", "使用在线学习平台",
    "需要购买指定教材", "推荐阅读书目较多", "有学术论文写作要求", "包含学术报告环节",
    "无特殊要求", "详见课程大纲", "", "暂无"
]

# --- 2. 用户生成函数 ---

def generate_chinese_username():
    """生成中文风格的用户名"""
    surname = random.choice(CHINESE_SURNAMES)
    given_name1 = random.choice(CHINESE_GIVEN_NAMES)
    given_name2 = random.choice(CHINESE_GIVEN_NAMES) if random.random() < 0.6 else ""
    return f"{surname}{given_name1}{given_name2}"

def generate_english_username():
    """生成英文风格的用户名"""
    first_name = random.choice(ENGLISH_FIRST_NAMES)
    last_name = random.choice(ENGLISH_LAST_NAMES)
    # 生成不同格式的用户名
    formats = [
        f"{first_name.lower()}.{last_name.lower()}",
        f"{first_name.lower()}{last_name.lower()}",
        f"{first_name[0].lower()}{last_name.lower()}",
        f"{first_name.lower()}{random.randint(10, 99)}"
    ]
    return random.choice(formats)

def generate_creative_username():
    """生成创意用户名"""
    base = random.choice(CREATIVE_USERNAMES)
    # 30% 概率加数字后缀
    if random.random() < 0.3:
        return f"{base}{random.randint(10, 999)}"
    # 20% 概率加下划线和第二个词
    elif random.random() < 0.2:
        second_word = random.choice(CREATIVE_USERNAMES)
        return f"{base}_{second_word}"
    else:
        return base

def generate_username(style="mixed"):
    """
    生成用户名
    style: "chinese", "english", "creative", "mixed"
    """
    if style == "chinese":
        return generate_chinese_username()
    elif style == "english":
        return generate_english_username()
    elif style == "creative":
        return generate_creative_username()
    else:  # mixed
        styles = [generate_chinese_username, generate_english_username, generate_creative_username]
        return random.choice(styles)()

def generate_email(username):
    """根据用户名生成邮箱"""
    # 对中文用户名进行简单的音译处理
    if any(ord(char) > 127 for char in username):
        # 简化的拼音映射（这里简化处理，实际可以用pypinyin库）
        pinyin_map = {
            '张': 'zhang', '李': 'li', '王': 'wang', '刘': 'liu', '陈': 'chen',
            '杨': 'yang', '黄': 'huang', '赵': 'zhao', '周': 'zhou', '吴': 'wu',
            '徐': 'xu', '孙': 'sun', '朱': 'zhu', '马': 'ma', '胡': 'hu',
            '郭': 'guo', '林': 'lin', '何': 'he', '高': 'gao', '梁': 'liang',
            '郑': 'zheng', '罗': 'luo', '宋': 'song', '谢': 'xie', '唐': 'tang',
            '韩': 'han', '冯': 'feng', '于': 'yu', '董': 'dong', '萧': 'xiao',
            '程': 'cheng', '曹': 'cao', '袁': 'yuan', '邓': 'deng', '许': 'xu',
            '傅': 'fu', '沈': 'shen', '曾': 'zeng', '彭': 'peng', '吕': 'lv',
            '晨': 'chen', '阳': 'yang', '雪': 'xue', '华': 'hua', '明': 'ming',
            '静': 'jing', '伟': 'wei', '娜': 'na', '磊': 'lei', '丽': 'li',
            '强': 'qiang', '敏': 'min', '涛': 'tao', '艳': 'yan', '超': 'chao',
            '洋': 'yang', '峰': 'feng', '霞': 'xia', '军': 'jun', '燕': 'yan',
            '辉': 'hui', '萍': 'ping', '鹏': 'peng', '红': 'hong', '斌': 'bin',
            '玲': 'ling', '勇': 'yong', '芳': 'fang', '杰': 'jie', '梅': 'mei',
            '宇': 'yu', '琳': 'lin', '飞': 'fei', '莉': 'li', '刚': 'gang',
            '倩': 'qian', '浩': 'hao', '婷': 'ting', '凯': 'kai', '欣': 'xin',
            '博': 'bo', '怡': 'yi', '龙': 'long', '佳': 'jia', '虎': 'hu',
            '慧': 'hui', '建': 'jian', '兰': 'lan', '文': 'wen', '英': 'ying'
        }
        
        email_prefix = ""
        for char in username:
            email_prefix += pinyin_map.get(char, char.lower())
    else:
        email_prefix = username.lower()
    
    domain = random.choice(EMAIL_DOMAINS)
    return f"{email_prefix}@{domain}"

def generate_users_data(num_additional_users=10, username_style="mixed"):
    """
    生成用户数据
    num_additional_users: 除了默认4个用户外，额外生成的用户数量
    username_style: 用户名风格 ("chinese", "english", "creative", "mixed")
    """
    # 保留原有的默认用户
    users_data = [
        {'username': 'admin', 'email': 'admin@example.com', 'role': 'ADMIN', 'is_enabled': 1},
        {'username': 'trial', 'email': 'trial@example.com', 'role': 'TRIAL', 'is_enabled': 1},
        {'username': 'user1', 'email': 'user1@example.com', 'role': 'USER', 'is_enabled': 1},
        {'username': 'user2', 'email': 'user2@example.com', 'role': 'USER', 'is_enabled': 0},
    ]
    
    # 生成额外的用户
    generated_usernames = set([user['username'] for user in users_data])
    
    for i in range(num_additional_users):
        # 确保用户名唯一
        attempts = 0
        while attempts < 50:  # 防止无限循环
            username = generate_username(username_style)
            if username not in generated_usernames:
                generated_usernames.add(username)
                break
            attempts += 1
        else:
            # 如果50次都没生成唯一用户名，就用后缀数字
            username = f"{generate_username(username_style)}_{i+5}"
        
        email = generate_email(username)
        
        # 随机分配角色（80%普通用户，15%试用用户，5%管理员）
        role_rand = random.random()
        if role_rand < 0.8:
            role = 'USER'
        elif role_rand < 0.95:
            role = 'TRIAL'
        else:
            role = 'ADMIN'
        
        # 90%的用户是启用状态
        is_enabled = 1 if random.random() < 0.9 else 0
        
        users_data.append({
            'username': username,
            'email': email,
            'role': role,
            'is_enabled': is_enabled
        })
    
    return users_data

# --- 3. 其他辅助函数保持不变 ---

def generate_random_timestamp(start_year=2022, end_year=2024):
    """生成一个指定年份范围内的随机时间戳字符串"""
    year = random.randint(start_year, end_year)
    month = random.randint(1, 12)
    day = random.randint(1, 28)
    hour = random.randint(0, 23)
    minute = random.randint(0, 59)
    second = random.randint(0, 59)
    dt = datetime.datetime(year, month, day, hour, minute, second)
    return dt.strftime('%Y-%m-%d %H:%M:%S')

def escape_sql(value):
    """简单的SQL字符串转义"""
    if isinstance(value, str):
        return "'" + value.replace("'", "''") + "'"
    return str(value)

def generate_teacher_email(teacher_name):
    """根据教师姓名生成邮箱"""
    if any(ord(char) > 127 for char in teacher_name):  # 中文姓名
        # 简单拼音转换映射
        pinyin_map = {
            '张': 'zhang', '李': 'li', '王': 'wang', '刘': 'liu', '陈': 'chen',
            '赵': 'zhao', '周': 'zhou', '黄': 'huang', '吴': 'wu', '徐': 'xu',
            '孙': 'sun', '马': 'ma', '朱': 'zhu', '胡': 'hu', '郭': 'guo',
            '何': 'he', '高': 'gao', '林': 'lin', '罗': 'luo', '梁': 'liang',
            '董': 'dong', '程': 'cheng', '石': 'shi', '贾': 'jia', '韩': 'han',
            '曹': 'cao', '彭': 'peng', '邓': 'deng', '范': 'fan', '田': 'tian',
            '蒋': 'jiang', '韦': 'wei', '卢': 'lu', '陆': 'lu', '易': 'yi',
            '钱': 'qian', '汪': 'wang', '于': 'yu', '任': 'ren', '廖': 'liao',
            '伟': 'wei', '静': 'jing', '英': 'ying', '洋': 'yang', '秀': 'xiu',
            '强': 'qiang', '敏': 'min', '磊': 'lei', '涛': 'tao', '明': 'ming',
            '丽': 'li', '超': 'chao', '华': 'hua', '军': 'jun', '艳': 'yan',
            '鹏': 'peng', '峰': 'feng', '娜': 'na', '斌': 'bin', '雪': 'xue',
            '建': 'jian', '亮': 'liang', '冰': 'bing', '阳': 'yang', '飞': 'fei',
            '野': 'ye', '勇': 'yong', '霞': 'xia', '杰': 'jie', '雷': 'lei'
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
    if prefix in ["腾讯会议"]:
        number = random.randint(100000000, 999999999)  # 9位会议号
        return f"{prefix}号: {number}"
    else:
        number = random.randint(100000000, 999999999)  # 9位群号
        return f"{prefix}: {number}"

def should_generate_field(probability):
    """按概率决定是否生成某个字段"""
    return random.random() < probability

# --- 4. 主要的SQL生成函数 ---

def generate_sql_script(num_additional_users=10, username_style="mixed"):
    """
    主函数，生成所有SQL INSERT语句
    num_additional_users: 除了默认4个用户外，额外生成的用户数量
    username_style: 用户名风格 ("chinese", "english", "creative", "mixed")
    """
    sql_statements = []

    # -- USERS -- 使用新的用户生成函数
    users_data = generate_users_data(num_additional_users, username_style)

    sql_statements.append("-- ----------------------------")
    sql_statements.append("-- Records of users")
    sql_statements.append("-- ----------------------------")
    for i, user in enumerate(users_data):
        user_id = i + 1
        created_at = generate_random_timestamp()
        updated_at = created_at
        sql = (
            f"INSERT INTO `users` (`id`, `username`, `password`, `email`, `role`, `is_enabled`, `created_at`, `updated_at`) VALUES "
            f"({user_id}, {escape_sql(user['username'])}, {escape_sql(PASSWORD_HASH)}, {escape_sql(user['email'])}, "
            f"{escape_sql(user['role'])}, {user['is_enabled']}, {escape_sql(created_at)}, {escape_sql(updated_at)});"
        )
        sql_statements.append(sql)

    term_id_counter = 1
    course_id_counter = 1
    schedule_id_counter = 1

    # 为启用的用户生成数据
    enabled_users = [(i+1, user) for i, user in enumerate(users_data) if user['is_enabled']]
    
    for user_id, user_info in enabled_users:
        # -- TERMS --
        sql_statements.append(f"\n-- Data for User ID: {user_id} ({user_info['username']}) --\n")
        sql_statements.append("-- ----------------------------")
        sql_statements.append(f"-- Records of terms for user {user_id}")
        sql_statements.append("-- ----------------------------")
        
        # 根据用户角色生成不同数量的学期
        if user_info['role'] == 'ADMIN':
            num_terms = random.randint(4, 6)
        elif user_info['role'] == 'TRIAL':
            num_terms = random.randint(2, 3)
        else:  # USER
            num_terms = random.randint(3, 4)
            
        user_terms = random.sample(list(TERM_NAMES.items()), min(num_terms, len(TERM_NAMES)))
        user_term_ids = []

        for term_name, (start_date, end_date) in user_terms:
            created_at = generate_random_timestamp()
            updated_at = created_at
            sql = (
                f"INSERT INTO `terms` (`id`, `user_id`, `name`, `start_date`, `end_date`, `created_at`, `updated_at`) VALUES "
                f"({term_id_counter}, {user_id}, {escape_sql(term_name)}, {escape_sql(start_date)}, {escape_sql(end_date)}, "
                f"{escape_sql(created_at)}, {escape_sql(updated_at)});"
            )
            sql_statements.append(sql)
            user_term_ids.append(term_id_counter)
            term_id_counter += 1

        # -- COURSES & SCHEDULE_ENTRIES --
        sql_statements.append("\n-- ----------------------------")
        sql_statements.append(f"-- Records of courses and schedules for user {user_id}")
        sql_statements.append("-- ----------------------------")
        
        for term_id in user_term_ids:
            # 根据用户角色生成不同数量的课程
            if user_info['role'] == 'ADMIN':
                num_courses = random.randint(8, 12)
            elif user_info['role'] == 'TRIAL':
                num_courses = random.randint(4, 6)
            else:  # USER
                num_courses = random.randint(6, 10)
                
            picked_course_names = random.sample(COURSE_NAMES, min(num_courses, len(COURSE_NAMES)))

            for course_name in picked_course_names:
                # -- Create a course --
                # 教师信息 (90%概率有教师)
                teachers_str = ""
                main_teacher_email = ""
                if should_generate_field(0.9):
                    num_teachers = random.randint(1, 3)
                    teachers_list = random.sample(TEACHERS, num_teachers)
                    teachers_str = ",".join(teachers_list)
                    
                    # 主讲教师邮箱 (60%概率)
                    if should_generate_field(0.6):
                        main_teacher = teachers_list[0]
                        main_teacher_email = generate_teacher_email(main_teacher)
                
                # 课程群号 (50%概率)
                course_group_chat_id = ""
                if should_generate_field(0.5):
                    course_group_chat_id = generate_group_chat_id()
                
                # 备注 (40%概率)
                note = ""
                if should_generate_field(0.4):
                    note = random.choice([n for n in COURSE_NOTES if n])  # 排除空字符串
                
                created_at = generate_random_timestamp()
                
                # 课程标签 (75%概率为必修)
                course_tag = 1 if random.random() < 0.75 else 0

                # 构建INSERT语句，包含所有字段
                sql = (
                    f"INSERT INTO `courses` (`id`, `user_id`, `term_id`, `name`, `teachers`, `main_teacher_email`, "
                    f"`course_group_chat_id`, `tag`, `note`, `created_at`, `updated_at`) VALUES "
                    f"({course_id_counter}, {user_id}, {term_id}, {escape_sql(course_name)}, "
                    f"{escape_sql(teachers_str)}, {escape_sql(main_teacher_email)}, "
                    f"{escape_sql(course_group_chat_id)}, {course_tag}, {escape_sql(note)}, "
                    f"{escape_sql(created_at)}, {escape_sql(created_at)});"
                )
                sql_statements.append(sql)

                # -- Create schedule entries for this course --
                # 根据课程类型生成不同的排程模式
                if "实验" in course_name or "实习" in course_name:
                    num_schedules = random.randint(1, 2)  # 实验课较少排程
                elif "体育" in course_name:
                    num_schedules = random.randint(2, 3)  # 体育课较多排程
                else:
                    num_schedules = random.randint(1, 3)  # 普通课程
                
                for _ in range(num_schedules):
                    # 上课地点 (85%概率有地点)
                    location = ""
                    if should_generate_field(0.85):
                        building = random.choice(LOCATIONS_BUILDINGS)
                        room = random.choice(ROOM_NUMBERS)
                        location = f"{building}-{room}"
                    
                    day_of_week = random.randint(1, 7)
                    
                    # 根据课程类型调整上课时间
                    if "体育" in course_name:
                        # 体育课通常在下午
                        start_period = random.randint(5, 8)
                        end_period = random.randint(start_period, start_period + 1)
                    elif "实验" in course_name:
                        # 实验课通常连续3-4节
                        start_period = random.randint(1, 8)
                        end_period = random.randint(start_period + 2, min(start_period + 4, 12))
                    else:
                        # 普通课程
                        start_period = random.randint(1, 10)
                        end_period = random.randint(start_period, min(start_period + 2, 12))
                    
                    # 周次安排更多样化
                    week_patterns = ['full_semester', 'first_half', 'second_half', 'custom_short', 'custom_long']
                    pattern = random.choice(week_patterns)
                    
                    if pattern == 'full_semester':
                        start_week, end_week = 1, 16
                    elif pattern == 'first_half':
                        start_week, end_week = 1, 8
                    elif pattern == 'second_half':
                        start_week, end_week = 9, 16
                    elif pattern == 'custom_short':
                        start_week = random.randint(1, 12)
                        end_week = random.randint(start_week + 2, min(start_week + 6, 16))
                    else:  # custom_long
                        start_week = random.randint(1, 4)
                        end_week = random.randint(start_week + 10, 20)

                    sql = (
                        f"INSERT INTO `schedule_entries` (`id`, `course_id`, `location`, `day_of_week`, "
                        f"`start_period`, `end_period`, `start_week`, `end_week`) VALUES "
                        f"({schedule_id_counter}, {course_id_counter}, {escape_sql(location)}, "
                        f"{day_of_week}, {start_period}, {end_period}, {start_week}, {end_week});"
                    )
                    sql_statements.append(sql)
                    schedule_id_counter += 1
                
                course_id_counter += 1

    return "\n".join(sql_statements), users_data

# --- 5. 命令行接口 ---
def main():
    parser = argparse.ArgumentParser(description='生成课程管理系统的测试SQL数据')
    parser.add_argument('-u', '--users', type=int, default=10, 
                       help='除了默认4个用户外，额外生成的用户数量 (默认: 10)')
    parser.add_argument('-s', '--style', choices=['chinese', 'english', 'creative', 'mixed'], 
                       default='mixed', help='用户名风格 (默认: mixed)')
    parser.add_argument('-o', '--output', type=str, help='输出文件名 (可选)')
    
    args = parser.parse_args()
    
    print(f"正在生成测试数据...")
    print(f"- 额外用户数量: {args.users}")
    print(f"- 用户名风格: {args.style}")
    print(f"- 总用户数: {4 + args.users}")
    
    final_sql, users_data = generate_sql_script(args.users, args.style)
    
    # 输出到文件或控制台
    if args.output:
        with open(args.output, 'w', encoding='utf-8') as f:
            f.write(final_sql)
        print(f"\n✅ SQL文件已生成: {args.output}")
    else:
        print("\n" + "="*80)
        print(final_sql)
    
    # 打印统计信息
    enabled_count = sum(1 for user in users_data if user['is_enabled'])
    role_stats = {}
    for user in users_data:
        role = user['role']
        role_stats[role] = role_stats.get(role, 0) + 1
    
    print("\n-- ----------------------------")
    print("-- 数据生成统计信息")
    print("-- ----------------------------")
    print(f"-- 用户总数: {len(users_data)}")
    print(f"-- 启用用户: {enabled_count}")
    print(f"-- 用户角色分布: {role_stats}")
    print(f"-- 课程名称池: {len(COURSE_NAMES)} 种")
    print(f"-- 教师名称池: {len(TEACHERS)} 人")
    print(f"-- 建筑地点池: {len(LOCATIONS_BUILDINGS)} 个")
    print(f"-- 教室编号池: {len(ROOM_NUMBERS)} 个")
    print(f"-- 学期类型: {len(TERM_NAMES)} 种")
    print(f"-- 用户名风格: {args.style}")
    print("-- 数据特点: 包含中英文教师、多样化课程类型、丰富的可选字段")
    print("-- ADMIN用户: 4-6个学期，每学期8-12门课程")
    print("-- TRIAL用户: 2-3个学期，每学期4-6门课程")
    print("-- USER用户: 3-4个学期，每学期6-10门课程")
    
    print("\n-- 生成的用户名示例:")
    for i, user in enumerate(users_data[:10]):  # 显示前10个用户
        print(f"-- {i+1:2d}. {user['username']:20s} ({user['role']:5s}) - {user['email']}")
    if len(users_data) > 10:
        print(f"-- ... 还有 {len(users_data)-10} 个用户")

# --- 6. 运行脚本 ---
if __name__ == "__main__":
    main()