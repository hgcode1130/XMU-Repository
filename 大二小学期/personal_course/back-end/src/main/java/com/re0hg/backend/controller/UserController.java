package com.re0hg.backend.controller;
import com.re0hg.backend.pojo.Result;
import com.re0hg.backend.mapper.UserMapper;
import com.re0hg.backend.service.UserService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RestController;

/**
 * @author re0hg
 * @version 1.0
 * @date 2025/6/22
 */
@RestController
@Slf4j
public class UserController {

    @Autowired
    private UserService userService;

}
