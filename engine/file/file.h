#include <error/engine_val.h>

namespace file{
    [[nodiscard]]
    engine::error::EngineVal<std::unique_ptr<uint8_t[]>> GetFileBuffer(const char* file_name,  size_t& size) noexcept;

    [[nodiscard]]
    engine::error::EngineVal<size_t> GetFileSize(const char* file_name) noexcept;
}

#include <iostream>
#include <cstdio>

#include <error/engine_val.h>


[[nodiscard]]
engine::error::EngineVal<size_t> file::GetFileSize(const char* file_name) noexcept{
    FILE* file = fopen(file_name, "r");
    if(!file){
        fclose(file);
        return {{__LINE__, "Error could not read file!"}};
    }
    
    fseek(file, 0, SEEK_END);
    size_t rv = ftell(file);
    fclose(file);
    return {rv};


}

[[nodiscard]]
engine::error::EngineVal<std::unique_ptr<uint8_t[]>> file::GetFileBuffer(const char* file_name,  size_t& size) noexcept{
    auto file_size_tpl = GetFileSize(file_name);
    if(file_size_tpl.IsError()){
        return {file_size_tpl.err};
    }
    const size_t file_size = file_size_tpl.val;
    
    auto rv = std::make_unique<uint8_t[]>(file_size);
    FILE *fp = fopen(file_name, "r");
    if(!fp){

        fclose(fp);
        return {{__LINE__, "Error coult not open file!"}};
    }
  

    fread(rv.get(), 1, file_size, fp);
    fclose(fp);

    return {std::move(rv)};
}