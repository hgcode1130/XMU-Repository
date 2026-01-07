#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <iomanip>
#include <random>

using namespace std;

// 封装文件系统类
class FileSystem {
private:
    static constexpr int BLOCK_SIZE = 2;      // 每块大小为2k
    static constexpr int TOTAL_BLOCKS = 500;  // 磁盘块总数

    struct File {
        int sizeKB;          // 文件占用空间（向上取整后的kB）
        vector<int> blocks;  // 分配的磁盘块索引列表
    };

    // Bitmap：0为空闲，1为占用
    vector<int> bitmap;
    map<string, File> fileTable;

    // 内部核心分配逻辑 (First-Fit 策略)
    vector<int> allocateInternal(int sizeInKB) {
        int blocksNeeded = (sizeInKB + BLOCK_SIZE - 1) / BLOCK_SIZE;
        vector<int> allocated;

        for (int i = 0; i < TOTAL_BLOCKS && blocksNeeded > 0; ++i) {
            if (bitmap[i] == 0) { // 找到空闲块
                bitmap[i] = 1;
                allocated.push_back(i);
                --blocksNeeded;
            }
        }

        // 如果剩余空间不足，执行回滚操作（原子性保证）
        if (blocksNeeded > 0) {
            for (int block : allocated) {
                bitmap[block] = 0;
            }
            allocated.clear();
        }

        return allocated;
    }

public:
    FileSystem() : bitmap(TOTAL_BLOCKS, 0) {}

    // 创建文件
    bool createFile(const string& name, double realSize) {
        // 向上取整逻辑保持不变
        int useSize = static_cast<int>(std::ceil(realSize));

        if (fileTable.find(name) != fileTable.end()) {
            cerr << "[Error] File " << name << " already exists!\n";
            return false;
        }

        vector<int> allocated = allocateInternal(useSize);
        if (allocated.empty()) {
            cerr << "[Error] Not enough space for file " << name << " (Size: " << useSize << "KB)\n";
            return false;
        }

        fileTable[name] = {useSize, allocated};
        return true;
    }

    // 删除文件
    bool deleteFile(const string& name) {
        auto it = fileTable.find(name);
        if (it == fileTable.end()) {
            cerr << "[Error] File " << name << " not found!\n";
            return false;
        }

        // 释放位图中的块
        for (int block : it->second.blocks) {
            bitmap[block] = 0;
        }

        fileTable.erase(it);
        return true;
    }

    // 显示文件分配表 (索引分配视图)
    void displayFileTable() const {
        cout << "\n" << string(60, '-') << "\n";
        cout << " [File Allocation Table]\n";
        cout << string(60, '-') << "\n";
        cout << left << setw(10) << "Filename" << setw(10) << "Size(KB)" << " Blocks Index\n";
        
        for (const auto& entry : fileTable) {
            cout << left << setw(10) << entry.first 
                 << setw(10) << entry.second.sizeKB << " [";
            const auto& blocks = entry.second.blocks;
            for (size_t i = 0; i < blocks.size(); ++i) {
                cout << blocks[i];
                if (i < blocks.size() - 1) cout << ",";
            }
            cout << "]\n";
        }
        cout << string(60, '-') << "\n";
    }

    // 显示空闲块 (增加换行，提高可读性)
    void displayFreeBlocks() const {
        cout << "\n[Free Blocks Visualization]\n";
        int count = 0;
        for (int i = 0; i < TOTAL_BLOCKS; ++i) {
            if (bitmap[i] == 0) {
                cout << setw(3) << i << " ";
                count++;
                if (count % 20 == 0) cout << "\n"; // 每行显示20个
            }
        }
        cout << "\nTotal Free Blocks: " << count << " / " << TOTAL_BLOCKS << "\n";
    }
};

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> sizeDist(2, 10); 

    FileSystem fs;

    cout << "Step 1: Randomly generating 50 files..." << endl;
    // (1) 随机生成 50 个文件并存储
    for (int i = 1; i <= 50; ++i) {
        int fileSize = sizeDist(gen); 
        fs.createFile(to_string(i) + ".txt", fileSize);
    }
    
    // 仅在关键步骤展示，避免刷屏，此处根据原意展示
    // fs.displayFileTable(); 

    cout << "Step 2: Deleting odd-numbered files..." << endl;
    // (2) 删除奇数编号文件
    for (int i = 1; i <= 50; i += 2) {
        fs.deleteFile(to_string(i) + ".txt");
    }

    // fs.displayFileTable();

    cout << "Step 3: Creating specific files (A, B, C, D, E)..." << endl;
    // (3) 创建 5 个新文件
    // 注意：浮点数 3.5 会在内部被 ceil 为 4
    fs.createFile("A.txt", 7);
    fs.createFile("B.txt", 5);
    fs.createFile("C.txt", 2);
    fs.createFile("D.txt", 9);
    fs.createFile("E.txt", 3.5); 

    // 最终展示结果
    fs.displayFileTable();
    fs.displayFreeBlocks();

    return 0;
}