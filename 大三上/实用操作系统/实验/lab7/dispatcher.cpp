#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

constexpr int PROCESS_NUM = 5;

struct Process {
    char name;          // 进程名称
    int arrive;         // 到达时间
    int time;           // 服务时间
    int start;          // 开始时间
    int end;            // 结束时间
    float rate;         // 响应比
    bool activated;     // 是否已到达/激活
    int rest;           // 剩余所需时间
};

// 定义初始状态模板，用于重置数据，避免在函数中硬编码数值
const vector<Process> INITIAL_PROCESSES = {
    {'A', 0, 3, 0, 0, 1.0f, false, 0},
    {'B', 2, 6, 0, 0, 1.0f, false, 0},
    {'C', 4, 4, 0, 0, 1.0f, false, 0},
    {'D', 6, 5, 0, 0, 1.0f, false, 0},
    {'E', 8, 2, 0, 0, 1.0f, false, 0}
};

// 全局工作容器
vector<Process> processes = INITIAL_PROCESSES;

// 重置函数：直接从模板复制，消除了硬编码的赋值操作
void resetProcesses() {
    processes = INITIAL_PROCESSES;
}

void printResult() {
    for (const auto& p : processes) {
        cout << p.name << " " 
             << p.end << " " 
             << (p.end - p.arrive) << " " 
             << p.rate << endl;
    }
}

// 先来先服务 (First Come First Serve)
void FCFS(vector<Process>& p) {
    int n = p.size();
    for (int i = 0; i < n; i++) {
        if (i > 0 && p[i].arrive < p[i - 1].end) {
            p[i].start = p[i - 1].end;
        } else {
            p[i].start = p[i].arrive;
        }
        
        p[i].end = p[i].start + p[i].time;
        p[i].rate = static_cast<float>(p[i].end - p[i].arrive) / p[i].time;
    }
    printResult();
}

// 时间片轮转 (Round Robin)
void RR(vector<Process>& p) {
    int n = p.size();
    queue<Process> q;
    
    // 备份原始数据以计算最终响应比 (因为 p[i].time 会被修改)
    vector<Process> backup = p; 

    int time_now = 0;
    q.push(p[0]);

    while (!q.empty()) {
        time_now++;
        Process temp = q.front();
        q.pop();
        temp.time--; // 执行一个时间片

        // 检查是否有新进程到达
        for (int i = 1; i < n; i++) {
            if (p[i].arrive == time_now) {
                q.push(p[i]);
            }
        }

        if (temp.time != 0) {
            q.push(temp); // 未完成，放回队列
        } else {
            // 进程完成，回写数据
            temp.end = time_now;
            for (int i = 0; i < n; i++) {
                if (temp.name == p[i].name) {
                    p[i] = temp;
                    // 使用备份的原始时间计算响应比
                    p[i].rate = static_cast<float>(p[i].end - p[i].arrive) / backup[i].time;
                    break;
                }
            }
        }
    }
    printResult();
}

// 最短进程优先 (Shortest Process Next)
void SPN(vector<Process>& p) {
    int n = p.size();
    int now = 0;
    int min_time = INT_MAX; // 优化：原代码为100，改为INT_MAX增加鲁棒性
    int time_now = p[0].arrive;

    // 循环 n 次，每次处理一个进程
    for (int i = 0; i < n; i++) {
        // 1. 激活所有已到达的进程
        for (int k = 0; k < n; k++) {
            if (p[k].arrive <= time_now && p[k].time != 0) {
                p[k].activated = true;
            }
        }

        // 2. 在已激活进程中找服务时间最短的
        for (int l = 0; l < n; l++) {
            if (p[l].activated && p[l].time < min_time) {
                min_time = p[l].time;
                now = l;
            }
        }

        // 3. 执行选中的进程
        p[now].start = time_now;
        p[now].end = p[now].start + p[now].time;
        time_now = p[now].end;
        p[now].rate = static_cast<float>(p[now].end - p[now].arrive) / p[now].time;
        
        // 标记为已完成
        p[now].activated = false;
        p[now].time = 0; // 这里的 time=0 用作“已完成”的标记
        min_time = INT_MAX;
    }
    printResult();
}

// 最短剩余时间优先 (Shortest Remaining Time)
void SRT(vector<Process>& p) {
    int n = p.size();
    int now = 0;
    int min_rest = INT_MAX;
    int time_now = p[0].arrive;

    // 初始化 rest 字段
    for (int i = 0; i < n; i++) {
        p[i].rest = p[i].time;
    }

    // 模拟每一个进程的处理过程
    for (int i = 0; i < n; i++) {
        // 模拟时间流逝的无限循环，直到选定并执行完一个片段或整个进程
        for (int j = 0;; j++) {
            // 激活到达的进程
            for (int k = 0; k < n; k++) {
                if (p[k].arrive <= time_now && p[k].time != 0) {
                    p[k].activated = true;
                }
            }

            // 选择剩余时间最短的进程
            for (int l = 0; l < n; l++) {
                if (p[l].activated && p[l].rest < min_rest) {
                    min_rest = p[l].rest;
                    now = l;
                }
            }

            p[now].start = time_now;

            // 检查是否有新进程在当前进程执行期间插入（抢占）
            int m = 0;
            for (m = 0; m < n; m++) {
                // 如果有其他进程(m)在当前进程(now)完成前到达，并且m比now短
                if (m != now && 
                    p[m].arrive < (time_now + p[now].rest) && 
                    p[m].time != 0 && 
                    !p[m].activated) 
                {
                    time_now = p[m].arrive; // 时间推进到新进程到达时刻
                    p[now].rest = p[now].start + p[now].rest - time_now; // 更新当前进程剩余时间
                    
                    if (p[m].rest < p[now].rest) {
                        now = m; // 发生抢占
                        break; 
                    }
                }
            }

            // 如果没有发生抢占 (m循环正常结束)
            if (m == n) {
                p[now].end = time_now + p[now].rest;
                time_now = p[now].end;
                p[now].rate = static_cast<float>(p[now].end - p[now].arrive) / p[now].time;
                p[now].activated = false;
                p[now].time = 0; // 标记完成
                break; // 跳出内层无限循环，进入下一个 i
            }
        }
        min_rest = INT_MAX;
    }
    printResult();
}

// 高响应比优先 (Highest Response Ratio Next)
void HRRN(vector<Process>& p) {
    int n = p.size();
    int now = 0;
    float max_rate = 1.0f; // 响应比最小为1
    int time_now = p[0].arrive;

    for (int i = 0; i < n; i++) {
        // 激活到达的进程
        for (int k = 0; k < n; k++) {
            if (p[k].arrive <= time_now && p[k].time != 0) {
                p[k].activated = true;
            }
        }

        // 计算响应比并找到最大的
        for (int l = 0; l < n; l++) {
            if (p[l].activated && p[l].time != 0) {
                // 响应比 = (等待时间 + 服务时间) / 服务时间
                p[l].rate = static_cast<float>(time_now + p[l].time - p[l].arrive) / p[l].time;

                if (max_rate < p[l].rate) {
                    max_rate = p[l].rate;
                    now = l;
                }
            }
        }

        // 执行选中的进程
        p[now].start = time_now;
        p[now].end = p[now].start + p[now].time;
        time_now = p[now].end;
        p[now].time = 0; // 标记完成
        
        // 重置 max_rate 用于下一轮比较
        max_rate = 1.0f; 
    }
    printResult();
}

int main() {
    // FCFS
    FCFS(processes);
    
    // RR
    resetProcesses();
    RR(processes);
    
    // SPN
    resetProcesses();
    SPN(processes);
    
    // SRT
    resetProcesses();
    SRT(processes);
    
    // HRRN
    resetProcesses();
    HRRN(processes);

    return 0;
}