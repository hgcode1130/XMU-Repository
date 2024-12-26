%清理工作区和命令行窗口
clc,clear

%变量赋值，输入矩阵
w = [1,2,3; 4,5,6; 7,8,9];

%操作矩阵
w1 = w(3);
w2 = w(1,2);
w3 = w(:,1);
w4 = w(1,:);
w5 = w(:,:);

%矩阵运算与数字运算
w * w;
w .* w;

%生成特定矩阵
x = [1:1:100];
y = [1:1:100];

%二维图像展示
%plot(x,y)

%三维图像展示
z = x.^2 + y.^2;
%plot3(x,y,z)

%导入数据展示
data_girl = xlsread('八年级女生体测数据.xlsx');

%散点图展示
%scatter(data_girl(:,1),data_girl(:,3));

%算法工具函数展示
Person = corrcoef(data_girl)

