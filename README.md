BitSet
===================

[![Build Status](https://travis-ci.org/weedge/bitset.svg)](https://travis-ci.org/weedge/bitset)
[![Code Climate](https://codeclimate.com/github/weedge/bitset/badges/gpa.svg)](https://codeclimate.com/github/weedge/bitset)

#### 介绍
将BitSet封装成类,用于php扩展调用

#### 场景(逼格data)
1. 比如倒排索引中两个倒排列表(DocList), 两个词在那些文档中同时出现(获取共现频率)
2. 统计大量数据中每一个数据出现次数(频率)    

#### todone
1. 不同bitset的与，非，或，异或逻辑（非运算需要截取后面多余部分）
2. 根据设定的位，来动态申请动态空间
3. 用valgrind工具检测内存泄露问题

#### todo
1. 第一个版本是以php方法的形式展现，后期版本采用类方法的形式
2. php扩展,内存用php-valgrind扩展来检测。

#### 测试用例
见tests中的测试用例，运行make test来测试吧~
