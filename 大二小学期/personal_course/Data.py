import random
import datetime
import bcrypt

# --- 1. 配置与数据池 ---

# 密码 '123456' 的 Bcrypt 哈希值 (每次运行脚本值都不同，但都有效)
PASSWORD_RAW = '123456'
PASSWORD_HASH = bcrypt.hashpw(PASSWORD_RAW.encode('utf-8'), bcrypt.gensalt()).decode('utf-8')

# 数据池
TERM_NAMES = {
    "2023-2024秋季学期": ("2023-09-01", "2024-01-11"),
    "2023-2024春季学期": ("2024-02-25", "2024-06-14"),
    "2023-2024夏季学期": ("2024-06-15", "2024-08-20"),
    "2024-2025春季学期": ("2025-02-10", "2025-06-19"),
    "2024-2025夏季学期": ("2025-06-20", "2025-08-22"),
    "2024-2025秋季学期": ("2024-09-01", "2025-01-19"),
}

LOCATIONS_BUILDINGS = ["学武楼", "西部片区二号楼", "西部片区四号楼", "益海嘉里楼", "坤乾楼", "文宣楼"]
ROOM_NUMBERS = ["101", "102", "103", "201", "202", "205", "301", "308", "404", "502"]

TEACHERS = ["张伟", "李静", "王英", "刘洋", "陈秀英", "赵强", "周敏", "黄磊"]

COURSE_NAMES = [
    "软件工程", "数据结构与算法", "计算机网络", "操作系统原理", "线性代数", "大学物理",
    "高级Web技术", "人工智能导论", "数据库系统", "编译原理", "数字逻辑设计", "面向对象程序设计"
]

# --- 2. 辅助函数 ---

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

# --- 3. 数据生成核心逻辑 ---

def generate_sql_script():
    """主函数，生成所有SQL INSERT语句"""
    sql_statements = []

    # -- USERS --
    users_data = [
        # id=1
        {'username': 'admin', 'email': 'admin@example.com', 'role': 'ADMIN', 'is_enabled': 1},
        # id=2
        {'username': 'trial', 'email': 'trial@example.com', 'role': 'TRIAL', 'is_enabled': 1},
        # id=3
        {'username': 'user1', 'email': 'user1@example.com', 'role': 'USER', 'is_enabled': 1},
        # id=4
        {'username': 'user2', 'email': 'user2@example.com', 'role': 'USER', 'is_enabled': 0},
    ]

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

    # 为启用的用户生成数据 (admin, trial, user1)
    for user_id in [1, 2, 3]:
        # -- TERMS --
        sql_statements.append(f"\n-- Data for User ID: {user_id} --\n")
        sql_statements.append("-- ----------------------------")
        sql_statements.append(f"-- Records of terms for user {user_id}")
        sql_statements.append("-- ----------------------------")
        
        # 为每个用户随机选3个学期
        user_terms = random.sample(list(TERM_NAMES.items()), 3)
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
            num_courses = random.randint(5, 8)
            picked_course_names = random.sample(COURSE_NAMES, num_courses)

            for course_name in picked_course_names:
                # -- Create a course --
                teachers_list = random.sample(TEACHERS, random.randint(1, 2))
                course_teachers_str = ",".join(teachers_list)
                note = random.choice(["期末开卷", "无", "有随堂测试", "重点课程，请注意听讲"])
                created_at = generate_random_timestamp()
                
                # 【新增】随机生成课程标签 (80%概率为必修)
                course_tag = 1 if random.random() < 0.8 else 0

                # 【修改】在 INSERT 语句中加入 tag 字段和值
                sql = (
                    f"INSERT INTO `courses` (`id`, `user_id`, `term_id`, `name`, `teachers`, `note`, `tag`, `created_at`, `updated_at`) VALUES "
                    f"({course_id_counter}, {user_id}, {term_id}, {escape_sql(course_name)}, {escape_sql(course_teachers_str)}, "
                    f"{escape_sql(note)}, {course_tag}, {escape_sql(created_at)}, {escape_sql(created_at)});"
                )
                sql_statements.append(sql)

                # -- Create schedule entries for this course --
                num_schedules = random.randint(1, 2) # 减少排程数量，避免数据过于密集
                for _ in range(num_schedules):
                    location = f"{random.choice(LOCATIONS_BUILDINGS)}-{random.choice(ROOM_NUMBERS)}"
                    day_of_week = random.randint(1, 7)
                    start_period = random.randint(1, 10)
                    end_period = random.randint(start_period, start_period + 1) # 1-2节的小课
                    if end_period > 12: end_period = 12
                    
                    start_week_type = random.choice(['full', 'half1', 'half2', 'custom'])
                    if start_week_type == 'full':
                        start_week, end_week = 1, 16
                    elif start_week_type == 'half1':
                        start_week, end_week = 1, 8
                    elif start_week_type == 'half2':
                        start_week, end_week = 9, 16
                    else: # custom
                        start_week = random.randint(1, 14)
                        end_week = random.randint(start_week + 1, 16)

                    sql = (
                        f"INSERT INTO `schedule_entries` (`id`, `course_id`, `location`, `day_of_week`, `start_period`, `end_period`, `start_week`, `end_week`) VALUES "
                        f"({schedule_id_counter}, {course_id_counter}, {escape_sql(location)}, {day_of_week}, {start_period}, {end_period}, {start_week}, {end_week});"
                    )
                    sql_statements.append(sql)
                    schedule_id_counter += 1
                
                course_id_counter += 1


    return "\n".join(sql_statements)


# --- 4. 运行并打印结果 ---
if __name__ == "__main__":
    final_sql = generate_sql_script()
    print(final_sql)