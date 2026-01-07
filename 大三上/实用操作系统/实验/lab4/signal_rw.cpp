// 读者-写者问题（Reader-Writer）：使用信号量实现“读者优先”方案
// - resource: 控制对共享资源的独占访问（写者独占，读者可并发）
// - read_mutex: 保护 readCount（当前正在读取的读者数）
// 读者优先：当有读者在读时，后来到的读者可以继续进入；写者需等待所有读者离开
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t resource;     // 对共享资源的互斥（写独占；第一位读者获取，最后一位读者释放）
sem_t read_mutex;   // 保护 readCount 的互斥量
int readCount = 0;  // 当前处于读状态的读者数量

void* reader(void* arg) {
    int id = *((int*)arg);
    while(1) {
        // 入场：更新读者计数；若是第一位读者，则锁住资源，阻止写者进入
        sem_wait(&read_mutex);
        readCount++;
        if (readCount == 1) {
            sem_wait(&resource);
        }
        sem_post(&read_mutex);

        // 临界区（读阶段）：多个读者可并发读取
        printf("Reader %d is reading.\n", id);
        sleep(3);

        // 离场：减少读者计数；若是最后一位读者，则释放资源，允许写者进入
        sem_wait(&read_mutex);
        readCount--;
        if (readCount == 0) {
            sem_post(&resource);
        }
        sem_post(&read_mutex);

        // 读者等待一段时间，模拟下一轮读取
        sleep(1);
    }
}

void* writer(void* arg) {
    int id = *((int*)arg);
    while(1) {
        // 写者需要对资源的独占访问
        sem_wait(&resource);

        printf("Writer %d is writing.\n", id);
        sleep(1);

        // 写完成后释放资源
        sem_post(&resource);

        sleep(1);
    }
}

int main() {
    pthread_t r1, r2, w1;
    int id1 = 1, id2 = 2, id3 = 1;

    // 初始化两个信号量为二进制信号量（互斥）
    sem_init(&resource, 0, 1);
    sem_init(&read_mutex, 0, 1);

    // 启动两个读者线程与一个写者线程
    pthread_create(&r1, NULL, reader, &id1);
    pthread_create(&r2, NULL, reader, &id2);
    pthread_create(&w1, NULL, writer, &id3);

    // 等待线程结束（本示例中循环不终止）
    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(w1, NULL);

    // 资源回收（若循环退出）
    sem_destroy(&resource);
    sem_destroy(&read_mutex);

    return 0;
}
