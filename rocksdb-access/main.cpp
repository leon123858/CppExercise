#include <iostream>
#include <rocksdb/db.h>
#include <rocksdb/iterator.h>

int main() {
    rocksdb::DB* db;
    rocksdb::Options options;
    options.create_if_missing = true;

    // 打开数据库
    rocksdb::Status status = rocksdb::DB::Open(options, "/path/to/your/db", &db);
    if (!status.ok()) {
        std::cerr << "Unable to open database: " << status.ToString() << std::endl;
        return 1;
    }

    rocksdb::ReadOptions read_options;
    rocksdb::Iterator* it = db->NewIterator(read_options);

    // 遍历键值对
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        std::cout << "Key: " << it->key().ToString() << ", Value: " << it->value().ToString() << std::endl;
    }

    if (!it->status().ok()) {
        std::cerr << "An error occurred while iterating: " << it->status().ToString() << std::endl;
    }

    delete it;
    delete db;
    return 0;
}
