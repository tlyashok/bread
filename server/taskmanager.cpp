#include "taskmanager.h"

// Все графы имеют 8 вершин

const int GRAPH_SIZE = 3;

QString TaskManager::create_task(int taskNumber)
{
    std::srand(std::time(nullptr));
    int genKey = rand();

    QStringList edges;
    QString taskText;

    switch (taskNumber) {
    case 1:
        taskText =
                "Дан граф, состоящий из 8 вершин. Все вершины пронумерованы от 1 до 8. "
                "Граф задан неориентированным рёбрами, приведёнными ниже: ";

        edges = create_task1(genKey).split(" ");

        for (auto i : edges) {
            taskText += i + ", ";
        }

        taskText.remove(taskText.size() - 2, 2); // Удаление последней запятой и пробела
        taskText += ". Найдите каркас графа. Задайте его рёбра через пробел.";
        return QString("get_task") + "$" + QString("1") + "$" + QString::number(genKey) + "$" + taskText;
        break;
    default:
        return create_task1(1); // В непредвиденном случае будет создаваться задание с ключом 1
        break;
    }
}

bool TaskManager::check_task(int taskNumber, int taskKey, QString answer)
{
    switch (taskNumber) {
    case 1:
        return check_task1(taskKey, answer);
    default:
        return false; // В непредвиденном случае будет создаваться задание с ключом 1
    }
}

bool hasCycle(const QVector<QVector<int>>& adjacencyMatrix) {
    int numVertices = adjacencyMatrix.size();
    QVector<bool> visited(numVertices, false);

    for (int startVertex = 0; startVertex < numVertices; ++startVertex) {
        if (!visited[startVertex]) {
            QSet<int> stack;
            QVector<int> parent(numVertices, -1);

            stack.insert(startVertex);
            visited[startVertex] = true;

            while (!stack.isEmpty()) {
                int currentVertex = *stack.begin();
                stack.erase(stack.begin());

                for (int neighbor = 0; neighbor < numVertices; ++neighbor) {
                    if (adjacencyMatrix[currentVertex][neighbor] == 1) {
                        if (!visited[neighbor]) {
                            stack.insert(neighbor);
                            visited[neighbor] = true;
                            parent[neighbor] = currentVertex;
                        } else if (parent[currentVertex] != neighbor) {
                            // Найден цикл, так как сосед уже посещен и не является родителем текущей вершины
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}

bool isGraphConnected(const QVector<QVector<int>>& adjacencyMatrix) {
    int numVertices = adjacencyMatrix.size();
    QVector<bool> visited(numVertices, false);

    QList<int> stack;
    stack.append(0); // Начинаем с вершины 0

    while (!stack.isEmpty()) {
        int currentVertex = stack.takeLast();

        if (!visited[currentVertex]) {
            visited[currentVertex] = true;

            for (int neighbor = 0; neighbor < numVertices; ++neighbor) {
                if (adjacencyMatrix[currentVertex][neighbor] == 1 && !visited[neighbor]) {
                    stack.append(neighbor);
                }
            }
        }
    }

    // Проверяем, все ли вершины были посещены
    for (bool isVisited : visited) {
        if (!isVisited) {
            return false; // Граф не является связанным
        }
    }

    return true; // Граф является связанным
}

bool TaskManager::check_task1(int taskKey, QString answer)
{
    try {
        QStringList edges = create_task1(taskKey).split(" ");
        QStringList edgesAns = answer.split(" ");
        QVector <QVector <int>> matrix (GRAPH_SIZE, QVector <int> (GRAPH_SIZE, 0));
        for (auto i : edges) {
            matrix[i[0].unicode()-'1'][i[1].unicode()-'1'] = 1;
            matrix[i[1].unicode()-'1'][i[0].unicode()-'1'] = 1;
        }
        QVector <QVector <int>> matrixAns (GRAPH_SIZE, QVector <int> (GRAPH_SIZE, 0));
        for (auto i : edgesAns) {
            matrixAns[i[0].unicode()-'1'][i[1].unicode()-'1'] = 1;
            matrixAns[i[1].unicode()-'1'][i[0].unicode()-'1'] = 1;
        }

        for (int i = 0; i < GRAPH_SIZE; i++) {
            for (int j = 0; j < GRAPH_SIZE; j++) {
                if (matrixAns[i][j] == 1 and matrix[i][j] == 0) {
                    return false;
                }
            }
        }
        if (hasCycle(matrixAns) or !isGraphConnected(matrixAns)) {
            return false;
        } else {
            return true;
        }

    } catch (...) {

        qDebug() << "Ошибка во время проверки задания." << "\n";
        return false;
    }
}

QString TaskManager::create_task1(int taskKey)
{
    srand(taskKey);
    QVector<QVector<int>> matrix(8, QVector<int>(8));
    for (int i = 0 ; i < GRAPH_SIZE; i++) {
        for (int j = 0; j < GRAPH_SIZE; j++) {
            if (i != j) {
                matrix[i][j] = rand() % 2;
            }
        }
    }

    for (int i = 1; i < GRAPH_SIZE; i++) {
        matrix[i][i-1] = 1;
        matrix[i-1][i] = 1;
    }

    QSet <QString> graphEdges;

    for (int i = 0 ; i < GRAPH_SIZE; i++) {
        for (int j = 0; j < GRAPH_SIZE; j++) {
            if (!graphEdges.contains(QString::number(j+1) + QString::number(i+1)) and matrix[i][j] == 1) {
                graphEdges.insert(QString::number(i+1) + QString::number(j+1));
            }
        }
    }

    QString edges;

    for (auto i : graphEdges) {
        edges += i + " ";
    }
    edges.remove(edges.size()-1,1);
    return edges;
}
