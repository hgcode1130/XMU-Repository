// 生产者-消费者示例：使用信号量与互斥量保护有界缓冲区
// - empty: 表示缓冲区中的空位数量
// - full:  表示缓冲区中的已用槽位数量
// - mutex: 用作对共享缓冲区/计数的互斥访问
// 注意：本示例为演示目的，使用无限循环与 sleep 模拟生产与消费速率
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];       // 有界缓冲区，大小为 BUFFER_SIZE
int count = 0;                 // 当前缓冲区中元素数量，同时也是下一个写入/读取的索引
sem_t empty, full, mutex;      // 三个信号量：空位、已满、互斥

void* producer(void* arg) {
    int item;
    while (1) {
        // 生成一个随机“产品”
        item = rand() % 100;

        // 若无空位则阻塞，确保不向满缓冲写入
        sem_wait(&empty);
        // 进入临界区，独占访问 buffer 与 count
        sem_wait(&mutex);

        // 将产品放入缓冲区尾部（栈式放置），并递增计数
        buffer[count++] = item;
        printf("Produced: %d\n", item);

        // 退出临界区
        sem_post(&mutex);
        // 增加“已用槽位”计数，唤醒可能等待的消费者
        sem_post(&full);

        // 模拟生产开销（生产速度快于消费以便观察阻塞切换）
        sleep(1);
    }
}

void* consumer(void* arg) {
    int item;
    while (1) {
        // 若无可消费的产品则阻塞
        sem_wait(&full);
        // 进入临界区，独占访问 buffer 与 count
        sem_wait(&mutex);

        // 从缓冲区尾部取出产品（与放入对称）
        item = buffer[--count];
        printf("Consumed: %d\n", item);

        // 退出临界区
        sem_post(&mutex);
        // 增加“空位”计数，唤醒可能等待的生产者
        sem_post(&empty);

        // 模拟消费开销（比生产慢，便于观察满/空转换）
        sleep(3);
    }
}

int main() {
    pthread_t prod, cons;

    // 初始化信号量：
    // empty 初值为缓冲区容量；full 初值为 0；mutex 为二进制互斥锁
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    // 启动生产者与消费者线程
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // 等待线程结束（本示例中为无限循环，理论上不会返回）
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // 资源回收（若上方循环退出）
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
