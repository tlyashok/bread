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
    case 3:
        taskText =
                "Дан граф, состоящий из от 6 вершин. Все вершины пронумерованы от 0 до 5. "
                "Граф задан ориентированными рёбрами с пропускной способностью, приведёнными ниже: ";

        edges = create_task3(genKey).split(" ");
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

//Функции и классы для третьего задания (Лещинский Р.А.)

struct Edge
{
    // Поток и макс.пропускная способность ребра
    int flow, capacity;

    // Ребро u--->v от ребра u
    // к ребру v.
    int u, v;

    Edge(int flow, int capacity, int u, int v)
    {
        this->flow = flow;
        this->capacity = capacity;
        this->u = u;
        this->v = v;
    }
};

struct Vertex
{
    int h, e_flow;

    Vertex(int h, int e_flow)
    {
        this->h = h;
        this->e_flow = e_flow;
    }
};

int  over_flow_vertex(QVector<Vertex>& ver)
{
    for (int i = 1; i < ver.size() - 1; i++)
       if (ver[i].e_flow > 0)
            return i;

    return -1;
}

class Graph
{
    int V;    // Количество вершин
    QVector<Vertex> ver;
    QVector<Edge> edge;

    bool push(int u)
    {
        // Проходим по всем рёбрам в поисках соседей, куда можно протолкну избыток
        for (int i = 0; i < edge.size(); i++)
        {
            // Проверка, что у ребра исток равен нашей вершине
            if (edge[i].u == u)
            {
                // Если поток по ребру равен пропускной способности, то протолкнуть больше не можем
                if (edge[i].flow == edge[i].capacity)
                    continue;

                // Проверка, что высота стока ребра меньше истока
                if (ver[u].h > ver[edge[i].v].h)
                {
                    int flow = std::min(edge[i].capacity - edge[i].flow,
                                   ver[u].e_flow);

                    ver[u].e_flow -= flow;

                    ver[edge[i].v].e_flow += flow;

                    edge[i].flow += flow;

                    //Добавление обратного ребра в остаточный граф
                    update_reverse_edge_flow(i, flow);

                    return true;
                }
            }
        }
        return false;
    }

    void relabel(int u)
    {
        // Для хранения минимальной высоты среди высот соседних вершин-стоков
        int mh = INT_MAX;

        // Поиск соседа-стока с минимальной высотой
        for (int i = 0; i < edge.size(); i++)
        {
            if (edge[i].u == u)
            {
                // Если поток равен пропускной способности, то не учитываем вершину
                if (edge[i].flow == edge[i].capacity)
                    continue;

                // Изменение высоты
                if (ver[edge[i].v].h < mh)
                {
                    mh = ver[edge[i].v].h;
                    ver[u].h = mh + 1;
                }
            }
        }
    }

    void preflow(int s)
    {
        // Устанавливаем высоту истока равной ко-ву вершин в графе
        ver[s].h = ver.size();

        //
        for (int i = 0; i < edge.size(); i++)
        {
            // Если вершины исходит из истока
            if (edge[i].u == s)
            {
                // Поток ребра приравниваем пропускной способности
                edge[i].flow = edge[i].capacity;

                // Делаем избыток вершин равным потоку
                ver[edge[i].v].e_flow += edge[i].flow;

                // Добавляем обратные рёбра в остаточный граф с пропускной способностью 0
                edge.push_back(Edge(-edge[i].flow, 0, edge[i].v, s));
            }
        }
    }

    void update_reverse_edge_flow(int i, int flow)
    {
        int u = edge[i].v, v = edge[i].u;

        for (int j = 0; j < edge.size(); j++)
        {
            if (edge[j].v == v && edge[j].u == u)
            {
                edge[j].flow -= flow;
                return;
            }
        }

        // Добавляем обратного рёбра в остаточный граф
        Edge e = Edge(0, flow, u, v);
        edge.push_back(e);
    }

public:
    Graph(int V)
    {
        this->V = V;

        // У всех вершин по умолчанию 0 избытка и 0 высота
        for (int i = 0; i < V; i++)
            ver.push_back(Vertex(0, 0));
    }

    void add_edge(int u, int v, int capacity)
    {
        // У всех рёбер изначально поток равен 0
        edge.push_back(Edge(0, capacity, u, v));
    }

    int get_max_flow(int s)
    {
        preflow(s);

        // Цикл до тех пор, пока не исчезнут все избытки у вершин
        while (over_flow_vertex(ver) != -1)
        {
            int u = over_flow_vertex(ver);
            if (!push(u))
                relabel(u);
        }

        // Возврат избытка последней вершины
        return ver.back().e_flow;
    }
};

int max_flow_search(QVector<QVector<int>> mass)
{
    int V = mass.back()[1] + 1;
    Graph g(V);

    for (int i = 0; i < mass.size(); i++)
        g.add_edge(mass[i][0], mass[i][1], mass[i][2]);
    int s = 0;

    qDebug() << "Максимальный поток " << g.get_max_flow(s);
    return 0;
}

QVector<QVector<int>> graph_generator(int key){
    srand(key);
    QVector<QVector<int>> mass;
    QVector<int> b;
    int ranges = 6;
    for (int i = 0; i < ranges; i++){
        b.append(i);
        b.append(i + 1);
        b.append(rand() % 10 + 5);
        mass.append(b);
        b.clear();
        for (int j = i + 1; j < ranges; j++){
            if (rand() % 10 > 4)
            {
                b.append(i);
                b.append(j + 1);
                b.append(rand() % 10 + 5);
                mass.append(b);
                b.clear();
            }
        }
    }
    return mass;
}

bool TaskManager::check_task3(int taskKey, QString answer)
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

QString TaskManager::create_task3(int taskKey)
{
    QVector<QVector<int>> i_edges = graph_generator(taskKey); //(вершина, вершина, пропускная способность) x 6

    QString edges; // Вершины слитно, через пробел пропускная способность x 6

    for (int i = 0; i < i_edges.size(); i++){
        edges += QString::number(i_edges[i][0]) + QString::number(i_edges[i][1]) + " " + QString::number(i_edges[i][2]);
        if (i != i_edges.size() - 1)
            edges += " ";
    }

    return edges;
}

//Конец функций и классов для третьего задания (Лещинский Р.А.)
