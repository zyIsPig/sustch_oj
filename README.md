# sustch_oj

## lab7 MST
- kruskal 并茶🐔 优化到On eloge e为边数量 
### lab7_1
- kruskal 裸题，注意优先队列速度比sort全排列要快。并茶🐔注意优化。1.查询时降低树高 2.合并时小的合到大的上

### lab7_2
- 假设知道a到c区间内的奇偶数，那么我们一但知道a到b区间内的奇偶数（假设b>c），则我们就可以知道了b到c区间内的奇偶数。
根据上述性质建模，将每一道题看成一个节点，引入0节点，默认0节点的奇偶是已知。边为查询当前节点到制定节点奇偶数的代价eg：0-3的边代表了查询0-3区间内奇偶数的代价。
根据上述性质，我们要知道所有节点的信息，只需要将所有节点联通即可->MST
