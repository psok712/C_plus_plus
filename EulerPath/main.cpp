#include <iostream>
#include <vector>

class Graph {
private:
    std::vector<std::vector<int>> vertices;
    std::vector<bool> visited;
public:
    Graph(std::vector<std::vector<int>> &list_vertex) {
        vertices.reserve(list_vertex.size());
        visited.reserve(list_vertex.size());

        for (auto &el : list_vertex) {
            vertices.emplace_back(el);
            visited.emplace_back(false);
        }
    }

    bool check_euler_path() {
        int count_odd_vertex = 0;

        for (auto &el : vertices) {
            if (el.size() % 2 != 0) {
                ++count_odd_vertex;

                if (count_odd_vertex > 2) {
                    return false;
                }
            }
            visited.emplace_back(false);
        }

        // Если граф неориентированный, то можно запустить для любой вершины BFS
        //BFS(2);

        // И так, если граф ориентированный
        for (int i = 0; i < vertices.size(); ++i) {
            if (!vertices[i].empty()) {
                DFS(i);
                break;
            }
        }

        // Проверка на количество компонент связности
        for (int i = 0; i < vertices.size(); ++i) {
            if (!vertices[i].empty() && !visited[i]) {
                return false;
            }
        }

        return true;
    }

    void DFS(int vertex) { // NOLINT
        visited[vertex] = true;

        for (auto &el : vertices[vertex]) {
            if (!visited[el]) {
                DFS(el);
            }
        }
    }
};

int main() {
    std::vector<std::vector<int>> vertices = {{1, 2}, {0, 2, 3, 4}, {0, 1, 3, 4}, {1, 2, 4, 5}, {1, 2, 3, 5}, {3, 4}};

    Graph graph(vertices);
    graph.DFS(2);
    std::cout << graph.check_euler_path() << std::endl;

    std::vector<std::vector<int>> vertices1 = {{1, 3, 2}, {0, 2, 3}, {1, 4, 0}, {0, 1}, {2}};

    Graph graph1(vertices1);
    std::cout << graph1.check_euler_path() << std::endl;


    std::vector<std::vector<int>> vertices2 = {{1, 3}, {0, 2, 3}, {1, 4}, {0, 1}, {2}};

    Graph graph2(vertices2);
    std::cout << graph2.check_euler_path() << std::endl;
    return 0;
}
