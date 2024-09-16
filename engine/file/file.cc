#include <iostream>
#include <cstdio>

#include <file/file.h>
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

engine::error::EngineVal<void> file::GetFileBuffer(const char* file_name, char* buffer, size_t& size) noexcept{
    auto file_size_tpl = GetFileSize(file_name);
    if(file_size_tpl.IsError()){
        return {file_size_tpl.err};
    }
    return {};
}