package com.re0hg.backend.controller;

import com.re0hg.backend.pojo.Result;
import com.re0hg.backend.utils.AliOSSUtils;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.multipart.MultipartFile;

import java.io.File;
import java.io.IOException;
import java.util.UUID;

/**
 * @author re0hg
 * @version 1.0
 * @date 2025/4/21
 */

@RestController
@Slf4j
public class UploadController {

    //本地存储
//    @PostMapping("/upload")
//    public Result upload(String username, Integer age, MultipartFile image){
//
//        String OriginalFilename = image.getOriginalFilename();
//
//        int index = OriginalFilename.lastIndexOf(".");
//        OriginalFilename = OriginalFilename.substring(index);
//        String newFileName = UUID.randomUUID().toString() + OriginalFilename;
//        try {
//            image.transferTo(new File("D:\\upload\\"+ newFileName));
//        } catch (IOException e) {
//            throw new RuntimeException(e);
//        }
//        return Result.success();
//    }
    @Autowired
    private AliOSSUtils aliOSSUtils;


    @PostMapping("/upload")
    public Result upload(MultipartFile image) throws IOException {
        log.info("文件上传,文件米：{}", image.getOriginalFilename());
        String url = aliOSSUtils.upload(image);
        return Result.success(200,"上传成功",url);
    }
}
