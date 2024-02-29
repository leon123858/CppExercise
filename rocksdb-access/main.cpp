#include <iostream>
#include <rocksdb/db.h>
#include <rocksdb/iterator.h>

std::string intToKey(int num)
{
    std::string key;
    key.resize(sizeof(int));
    for (size_t i = 0; i < sizeof(int); ++i) {
        key[sizeof(int) - i - 1] = (num >> (i * 8)) & 0xFF;
    }
    return key;
}
int keyToInt(const std::string& key)
{
    int num = 0;
    for (size_t i = 0; i < sizeof(int); ++i) {
        num = (num << 8) | static_cast<unsigned char>(key[i]);
    }
    return num;
}

int main()
{
    rocksdb::DB* db;
    rocksdb::Options options;
    options.create_if_missing = true;

    // 打开数据库
    rocksdb::Status status = rocksdb::DB::Open(options, "/root/.bitcoin/regtest/contracts/block_index", &db);
    if (!status.ok()) {
        std::cerr << "Unable to open database: " << status.ToString() << std::endl;
        return 1;
    }

    rocksdb::ReadOptions read_options;
    rocksdb::Iterator* it = db->NewIterator(read_options);

    int max = -1;

    // 遍历键值对
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        max = std::max(max, keyToInt(it->key().ToString()));
        std::cout << "Key: " << keyToInt(it->key().ToString()) << ", Value: " << it->value().ToString() << std::endl;
    }

    if (!it->status().ok()) {
        std::cerr << "An error occurred while iterating: " << it->status().ToString() << std::endl;
    }

    // remove
    db->Delete(rocksdb::WriteOptions(), intToKey(max));

    // add
    std::string value = "5a0c6b49882a9f981bad0848490275cee3a88c91d1b7e4a0c9ac06b1a7eb9d88";
    db->Put(rocksdb::WriteOptions(), intToKey(max), value);

    delete it;
    delete db;
    return 0;
}
