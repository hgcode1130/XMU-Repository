import java.io.BufferedReader; // 新增导入
import java.io.IOException;
import java.io.InputStream;    // 新增导入
import java.io.InputStreamReader; // 新增导入
import java.nio.charset.StandardCharsets; // 新增导入，用于指定编码
import java.util.Arrays;
import java.util.Map;
import java.util.stream.Collectors;

/**
 * @author re0hg
 * @version 1.0
 * @date 2025/5/28
 */

/*
读入一个txt文件，用Lambdas表达式和Stream流统计文件中单词的出现个数，并以字母分组输出。
 */

public class Problem {

    public static void main(String[] args) {
        // 定义资源文件在classpath中的路径。
        String resourceFileName = "words.txt";

        try {
            // 通过 ClassLoader 获取资源的 InputStream
            // 这种方式可以找到在 classpath 中的资源，无论是文件系统中的文件还是 JAR 包中的文件
            InputStream inputStream = Problem.class.getClassLoader().getResourceAsStream(resourceFileName);

            if (inputStream == null) {
                System.err.println("错误：在 classpath 中找不到资源文件 '" + resourceFileName + "'。");
                System.err.println("请确保 'words.txt' 位于 'src/main/resources' 目录下。");
                return; // 如果找不到文件，则提前退出
            }

            // 使用 try-with-resources 确保 InputStream 和 BufferedReader 自动关闭
            try (BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream, StandardCharsets.UTF_8))) {
                // 从 BufferedReader 中获取行的Stream流
                Map<Character, Map<String, Long>> wordsGroupedByFirstLetter =
                        reader.lines() // 获取文件中的每一行，形成一个行的Stream流
                                // 将每一行文本转换为小写，然后按非单词字符（如空格、标点符号）分割成单词数组
                                // 最后使用 flatMap 将所有行的单词Stream扁平化为一个总的单词Stream
                                .flatMap(line -> Arrays.stream(line.toLowerCase().split("\\W+")))
                                .filter(word -> !word.isEmpty()) // 过滤掉因分割可能产生的空字符串
                                // 可选：确保单词的第一个字符是字母，这样才能按字母分组
                                .filter(word -> Character.isLetter(word.charAt(0)))
                                .collect(Collectors.groupingBy( // 第一次分组：根据单词的第一个字符进行分组
                                        word -> word.charAt(0), // 分组键是单词的第一个字符
                                        Collectors.groupingBy( // 第二次（嵌套）分组：对第一个字符相同的单词，再按单词本身进行分组
                                                word -> word, // 分组键是单词本身（或使用 Function.identity()）
                                                Collectors.counting() // 对每个单词进行计数，统计其出现次数
                                        )
                                ));

                // 输出结果，为了显示整洁，按首字母进行排序。
                wordsGroupedByFirstLetter.entrySet().stream()
                        // 对最外层的 Map（按首字母分组的 Map）的 Entry 进行排序，按键（首字母）进行升序排列
                        .sorted(Map.Entry.comparingByKey())
                        .forEach(entry -> {
                            char firstLetter = entry.getKey(); // 获取当前分组的首字母
                            Map<String, Long> wordCounts = entry.getValue(); // 获取该首字母对应的单词及其计数

                            System.out.println("--- 单词以 '" + Character.toUpperCase(firstLetter) + "' 开头 ---");
                            // 对每个首字母下的单词及其计数进行排序，按单词本身进行字母排序，以便输出整齐
                            wordCounts.entrySet().stream()
                                    .sorted(Map.Entry.comparingByKey())
                                    .forEach(wordEntry -> {
                                        System.out.println("  " + wordEntry.getKey() + ": " + wordEntry.getValue());
                                    });
                            System.out.println(); // 每个分组后添加空行，增加可读性
                        });
            } // BufferedReader 和 InputStream 在这里自动关闭
        } catch (IOException e) {
            System.err.println("处理文件时发生错误: " + e.getMessage());
            e.printStackTrace();
        } catch (Exception e) {
            System.err.println("发生未知错误: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
