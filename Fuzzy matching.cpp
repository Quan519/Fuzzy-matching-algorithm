class Solution {
public:
    int patternMatch(string haystack, string needle) {
        int h_len = haystack.size(), n_len = needle.size();
        if (!n_len)
            return 0;
            
        // 预处理
        int shift[0xFF + 1]{}; // 字符偏移表
        int wildcard_min_shitf = 0;  // 通配符最小偏移
        for (int i = 0; i < n_len; ++i) {
            if (needle[i] == '?')// 将 ? 的最小偏移量存到 wildcard_min_shitf 里
                wildcard_min_shitf = n_len - i;
            else
                shift[needle[i]] = n_len - i;
        }

        for (int i = 0; i <= h_len - n_len;) { // i 主串指针
            bool found = true;
            int step = wildcard_min_shitf; // 每次对比之前重置为最小偏移量
            for (int j = 0; j < n_len; ++j) { // j 模式串指针
                if (needle[j] == '?') // 遇到?，更新通配符偏移
                    step = n_len - j;
                else if (haystack[i + j] != needle[j]) {  // 不匹配
                    found = false;
                    break;
                }
            }

            if (found)  // 匹配，返回索引
                return i;

            // 不匹配，如果参与匹配的末尾字符的下一位在字符偏移表里，就使用字符偏移量
            if (int shift_step = shift[haystack[i + n_len]]) {
                step = shift_step; 
            }

            if (step > 0) {
                i += step;  // 出现在模式串中，按偏移量跳过
            } else {
                i += n_len + 1; // 没出现在模式串中，跳过模式串长度 + 1
            }
        }

        return -1;
    }
};
