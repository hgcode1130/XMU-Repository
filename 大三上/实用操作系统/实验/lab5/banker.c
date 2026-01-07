#include <stdio.h>
#include <stdbool.h>

// 进程数和资源数
#define NUM_PROCESSES 5 /
#define NUM_RESOURCES 3 

// 可用资源向量 (Available)
int g_available[NUM_RESOURCES] = {3, 3, 2};

// 最大需求矩阵 
int g_maximum[NUM_PROCESSES][NUM_RESOURCES] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

// 分配矩阵
int g_allocation[NUM_PROCESSES][NUM_RESOURCES] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

// 需求矩阵 (Need)
int g_need[NUM_PROCESSES][NUM_RESOURCES];

// --- 辅助函数：打印当前系统状态 ---
void printSystemState() {
    printf("\n------------------------------------------------\n");
    printf("当前系统资源状态:\n");
    printf("进程ID | 分配矩阵  | 需求矩阵 \n");
    printf("-------|-----------------------|----------------\n");
    
    for (int i = 0; i < NUM_PROCESSES; i++) {
        printf("  P%d  | ", i);
        for (int j = 0; j < NUM_RESOURCES; j++) printf("%2d ", g_allocation[i][j]);
        printf("      | ");
        for (int j = 0; j < NUM_RESOURCES; j++) printf("%2d ", g_need[i][j]);
        printf("\n");
    }

    printf("\n系统可用资源 (Available): [ ");
    for (int i = 0; i < NUM_RESOURCES; i++) {
        printf("%d ", g_available[i]);
    }
    printf("]\n------------------------------------------------\n");
}

// --- 步骤 1: 初始化需求矩阵 ---
// Need[i][j] = Maximum[i][j] - Allocation[i][j]
void calculateNeed() {
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            g_need[i][j] = g_maximum[i][j] - g_allocation[i][j];
        }
    }
}

// --- 步骤 2: 安全性检查算法 ---
bool checkSafetyState() {
    int work_vector[NUM_RESOURCES]; // 工作向量
    bool finish[NUM_PROCESSES] = {false}; // 完成状态
    int safe_sequence[NUM_PROCESSES]; // 记录安全序列
    int count = 0;

    // 初始化工作向量等于当前可用资源
    for (int i = 0; i < NUM_RESOURCES; i++) {
        work_vector[i] = g_available[i];
    }

    // 寻找安全序列
    while (count < NUM_PROCESSES) {
        bool found_process = false;

        for (int p = 0; p < NUM_PROCESSES; p++) {
            // 如果进程未完成
            if (!finish[p]) {
                // 检查该进程的需求是否小于等于当前工作向量 (Need <= Work)
                bool can_allocate = true;
                for (int j = 0; j < NUM_RESOURCES; j++) {
                    if (g_need[p][j] > work_vector[j]) {
                        can_allocate = false;
                        break;
                    }
                }

                // 如果满足条件，模拟回收资源
                if (can_allocate) {
                    for (int k = 0; k < NUM_RESOURCES; k++) {
                        work_vector[k] += g_allocation[p][k];
                    }
                    safe_sequence[count++] = p;
                    finish[p] = true;
                    found_process = true;
                }
            }
        }

        // 如果一轮循环下来没有找到任何可执行的进程，说明系统不安全
        if (!found_process) {
            return false;
        }
    }

    printf(">> 检测结果：系统处于安全状态。\n");
    printf(">> 安全序列: ");
    for (int i = 0; i < NUM_PROCESSES; i++) {
        printf("P%d%s", safe_sequence[i], (i < NUM_PROCESSES - 1) ? " -> " : "");
    }
    printf("\n");
    return true;
}

// --- 步骤 3: 处理资源请求 ---
void handleResourceRequest(int process_id, int request[]) {
    printf("\n>>> 进程 P%d 发起请求: [ ", process_id);
    for (int i = 0; i < NUM_RESOURCES; i++) printf("%d ", request[i]);
    printf("]\n");

    // 逻辑判断 1: 请求是否超过声明的最大需求 (Request <= Need)
    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (request[i] > g_need[process_id][i]) {
            printf("错误：请求资源数超过了该进程宣布的最大需求 (Need)。\n");
            return;
        }
    }

    // 逻辑判断 2: 请求是否超过当前系统可用资源 (Request <= Available)
    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (request[i] > g_available[i]) {
            printf("等待：当前系统资源不足，进程需等待。\n");
            return;
        }
    }

    // 试探性分配 (Trial Allocation)
    for (int i = 0; i < NUM_RESOURCES; i++) {
        g_available[i] -= request[i];
        g_allocation[process_id][i] += request[i];
        g_need[process_id][i] -= request[i];
    }

    // 执行安全性检查
    if (checkSafetyState()) {
        printf("成功：资源已正式分配给进程 P%d。\n", process_id);
        printSystemState();
    } else {
        // 恢复现场 (Rollback)
        printf("警告：分配会导致死锁 (不安全状态)。请求被拒绝，状态已回滚。\n");
        for (int i = 0; i < NUM_RESOURCES; i++) {
            g_available[i] += request[i];
            g_allocation[process_id][i] -= request[i];
            g_need[process_id][i] += request[i];
        }
    }
}

int main() {
    calculateNeed(); // 初始化 Need 矩阵
    printSystemState(); // 打印初始状态

    int process_id;
    int request[NUM_RESOURCES];

    while (true) {
        printf("\n请输入请求资源的进程ID (输入 -1 退出): ");
        if (scanf("%d", &process_id) != 1 || process_id == -1) {
            break;
        }

        // 简单的输入校验
        if (process_id < 0 || process_id >= NUM_PROCESSES) {
            printf("无效的进程ID，请重试。\n");
            continue;
        }

        printf("请输入 %d 类资源的请求数量 (空格分隔): ", NUM_RESOURCES);
        for (int i = 0; i < NUM_RESOURCES; i++) {
            scanf("%d", &request[i]);
        }

        // 处理请求
        handleResourceRequest(process_id, request);

        // 清理输入缓冲区，防止字符残留导致下一次读取错误
        while (getchar() != '\n'); 
    }

    printf("程序已退出。\n");
    return 0;
}