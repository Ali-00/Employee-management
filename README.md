# B-Tree Based Employee Management System
Employee management systems are useful for running a smooth organization, especially organizations of scale. It assists HR personnel to keep track of employee information such as salary details, medical information, attendance/leave records, overall performance and more.This employee management system is build using B-Tree base algorithm for optimizing search.

B-Tree is a self-balancing search tree. In most of the other self-balancing search trees (like AVL and Red-Black Trees), it is assumed that everything is in main memory. To understand the use of B-Trees, we must think of the huge amount of data that cannot fit in main memory. When the number of keys is high, the data is read from disk in the form of blocks. Disk access time is very high compared to the main memory access time. The main idea of using B-Trees is to reduce the number of disk accesses. Most of the tree operations (search, insert, delete, max, min ) require O(h) disk accesses where h is the height of the tree. B-tree is a fat tree. The height of B-Trees is kept low by putting maximum possible keys in a B-Tree node. Generally, the B-Tree node size is kept equal to the disk block size. Since the height of the B-tree is low so total disk accesses for most of the operations are reduced significantly compared to balanced Binary Search Trees like AVL Tree, Red-Black Tree.
Every node has at most m children.
Every non-leaf node (except root) has at least ⌈m/2⌉ child nodes.
The root has at least two children if it is not a leaf node.
A non-leaf node with k children contains k − 1 keys.
All leaves appear in the same level and carry no information.
