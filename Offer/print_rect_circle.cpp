/*
 * 顺时针打印矩阵
 */

class Solution {
    public:
        vector<int> printMatrix(vector<vector<int> > matrix) {
            vector<int> result;
            int rows = matrix.size();
            if (rows == 0) {
                return result;
            }

            int cols = matrix[0].size();
            int circle = (((cols>rows)?rows:cols) - 1) / 2 + 1;

            for (int start = 0; start < circle; start++) {
                printMatrixCircle(matrix, rows, cols, start, result);
            }

            return result;
        }

        void printMatrixCircle(vector<vector<int> > matrix, int rows, int cols, int start, vector<int> &result) {
            int endCol = cols - start;
            int endRow = rows - start; 

            /* 从左到右打印 */
            for (int i = start; i < endCol; i++) {
                result.push_back(matrix[start][i]);
            }
            
            for (int i = start + 1; i < endRow; i++) {
                result.push_back(matrix[i][endCol-1]);
            }

            /* 从右到左打印, 防止单行情况 */
            for (int i = endCol - 2; (i >= start) && (endRow - 1 != start);i--) {
                result.push_back(matrix[endRow-1][i]);
            }

            /* 从下到上打印, 防止单列情况 */
            for (int i = endRow - 2; (i >= start + 1) && (endCol - 1 != start); i--) {
                result.push_back(matrix[i][start]);
            }
        }
};
