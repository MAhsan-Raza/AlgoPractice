#pragma once

vector<int> GraphDFS(const int V, const vector<vector<int>>& adj)
{
    vector<int> res;
    vector<bool> vztdNds(V, false);

    function<void(int)> getGrpDFS = [&](const int Vi)
    {
        res.push_back(Vi);
        vztdNds[Vi] = true;
        if (Vi < V)
        {
            for (const int vs : adj[Vi])
            {
                if (false == vztdNds[vs])
                    getGrpDFS(vs);
            }
        }
    };

    getGrpDFS(0);
    return res;
}

vector<int> GraphBFS(int V, const vector<vector<int>>& adj)
{
    vector<bool> vztds(V, false);
    vector<int> res; res.reserve(V);

    queue<int> q;
    q.push(0);
    vztds[0] = true;

    while (false == q.empty())
    {
        int crnt = q.front();
        q.pop();

        res.push_back(crnt);

        for (auto x : adj[crnt])
        {
            if (false == vztds[x])
            {
                q.push(x);
                vztds[x] = true;
            }
        }
    }

    return res;
}

int orangesRotting(vector<vector<int>>& grid)
{
    using CellStatus = enum
    {
        Empty = 0,
        Fresh,
        Rotten
    };
    using Cell = pair<int, int>;
    using CellsVec = vector<Cell>;

    // IterateAll -> IsFresh , BreakOnFirst
    // Enque all rottens
    // increase count when rotting first orrange in a level
    //      i.e. we will inc the count when swaping the from the SideQ & if SideQ is not empty
    // GetAllNeighbours & push to side q
    // if freshRemaining? return -1 : return rottenLevels

    if (grid.empty()) return 0;

    int rowLimit = grid.size();
    int colLimit = grid.front().size();

    bool freshRemaining = false;
    int rottenLevels = 0;
    queue<Cell> qMain, qSide;

    function<bool(Cell&)> NextCell = [&](Cell& cell)->bool
    {
        ++cell.second;
        if (cell.second == colLimit)
        {
            cell.second = 0;
            ++cell.first;
            if (cell.first == rowLimit)
                return false;
        }
        return true;
    };

    function<bool(Cell&)> PushRottensToQ = [&](Cell& cell)->bool
    {
        if (grid[cell.first][cell.second] == CellStatus::Rotten)
            qMain.push(cell);

        return NextCell(cell);
    };

    function<bool(Cell&)> DetectFresh = [&](Cell& cell)->bool
    {
        if (grid[cell.first][cell.second] == CellStatus::Fresh)
        {
            freshRemaining = true;
            return false;
        }
        return NextCell(cell);
    };

    function<void(function<bool(Cell&)>)> IterateAll = [](function<bool(Cell&)> dlgt)
    {
        auto firstCell = make_pair(0, 0);
        while (dlgt(firstCell));
    };


    function<void(const Cell&, CellsVec&)> GetNeighbours = [rowLimit, colLimit](const Cell& cell, CellsVec& nghbrs)
    {
        nghbrs.clear();
        if (cell.first > 0)
            nghbrs.emplace_back(cell.first - 1, cell.second);

        if (cell.first < rowLimit - 1)
            nghbrs.emplace_back(cell.first + 1, cell.second);

        if (cell.second > 0)
            nghbrs.emplace_back(cell.first, cell.second - 1);

        if (cell.second < colLimit - 1)
            nghbrs.emplace_back(cell.first, cell.second + 1);
    };

    IterateAll(PushRottensToQ);

    CellsVec nghbrs;

    while (true)
    {
        if (qMain.empty())
        {
            if (qSide.empty())
                break;

            ++rottenLevels;
            qMain.swap(qSide);
        }

        Cell crnt = qMain.front();
        qMain.pop();

        GetNeighbours(crnt, nghbrs);
        for (int i = 0; i < nghbrs.size(); i++)
        {
            Cell& cell = nghbrs[i];
            if (grid[cell.first][cell.second] == CellStatus::Fresh)
            {
                grid[cell.first][cell.second] = CellStatus::Rotten;
                qSide.push(cell);
            }
        }
    }

    IterateAll(DetectFresh);

    return freshRemaining ? -1 : rottenLevels;
}

// Slow -> N times DFS(s)
bool isCyclic_DirectedGraph_Slow(int V, const vector<vector<int>>& adj)
{
    // BFS or DFS from each node
    // if arrived on originating node return true
    // return false

    int NUM_JUMPS = 0;

    function<bool(const int, const int, vector<bool>&)>
        TryToReachOrigin = [&](const int nodeNum, const int origNode, vector<bool>& vztdNodes)
        ->bool
    {
        ++NUM_JUMPS;
        for (const int nghbr : adj[nodeNum])
        {
            if (nghbr == origNode)
                return true;

            if (false == vztdNodes[nghbr])
            {
                vztdNodes[nghbr] = true;
                if (TryToReachOrigin(nghbr, origNode, vztdNodes))
                    return true;
            }
        }

        return false;
    };
    

    for (int i = 0; i < V; i++)
    {
        vector<bool> vztdNodes(V, false);
        vztdNodes[i] = true;

        if (TryToReachOrigin(i, i, vztdNodes))
            return true;
    }

    return false;
}

// Fast -> Only 1 times DFS required
// DFS of a graph generates a tree
// Perform DFS from 'each' node & maintain a recursive stack when enters a node's function mark it True & when returning mark it False
// Also maintain a vztdNodes vector
// Whenever we found crnt node to be its parent itself return true
    // A node will not dectet an existing loop IfAndOnlyIf crnt node belongs to an isolated (disconnected) island
bool isCyclic_DirectedGraph(int V, const vector<vector<int>>& adj)
{
    vector<bool> vztdNodes(V, false);
    vector<bool> crntStack(V, false);

    function<bool(const int)> dfsGrphIsLoop = [&](const int indx)->bool
    {
        crntStack[indx] = true;
        vztdNodes[indx] = true;

        for (const int nghbr : adj[indx])
        {
            if (crntStack[nghbr])
                return true;

            if (false == vztdNodes[nghbr])
                if (dfsGrphIsLoop(nghbr))
                    return true;

        }

        crntStack[indx] = false;
        return false;
    };

    for (int i = 0; i < V; i++)
        if (dfsGrphIsLoop(i))
            return true;

    return false;
}

bool isCycle_UnDirectedGraph(int V, const vector<vector<int>>& adj)
{
    vector<int> StkTrace;
    vector<bool> vztdNodes;

    function<bool(int)> dfsCycleUD = [&](const int indx)->bool
    {
        StkTrace.push_back(indx);
        vztdNodes[indx] = true;

        for (const int nghbr : adj[indx])
        {
            if (StkTrace.size() >= 2 && StkTrace.end()[-2] == nghbr)
                continue;
            if (vztdNodes[nghbr] || dfsCycleUD(nghbr))
                return true;
        }

        StkTrace.pop_back();
        return false;
    };

    for (int i = 0; i < V; i++)
    {
        vztdNodes = vector<bool>(V, false);
        if (dfsCycleUD(i))
            return true;
    }

    return false;
}

void testGraphTheory()
{
    /*GraphDFS(8,
        {
            {4, 6, 7},
            {6},
            {5},

            {6},
            {},
            {6},

            {},
            {},
        }
    );

    GraphBFS(10,
        {
            {2, 3, 4, 5, 6, 7},
            {2, 3, 4, 5, 7, 8},
            {3, 5, 7, 8, 9},

            {4, 7, 8, 9},
            {5},
            {7, 9},

            {8},
            {},
            {9},

            {}
        }
    );

    vector<vector<int>> x;
    orangesRotting(x =
        {
            {2, 1},
            {1, 1}
        }
    );
    orangesRotting(x =
        {
            {2, 1},
            {1, 0}
        }
    );
    orangesRotting(x =
        {
            {2, 0},
            {0, 0}
        }
    );
    orangesRotting(x =
        {
            {1, 0},
            {1, 2}
        }
    );
    orangesRotting(x =
        {
            {2, 0},
            {0, 1}
        }
    );
    orangesRotting(x =
        {
            {0, 1, 2},
            {0, 1, 2},
            {2, 1, 1}
        }
    );
    orangesRotting(x =
        {
            {2, 2, 0, 1}
        }
    );
    orangesRotting(x = 
        { 
            {2, 1, 1},
            {1, 1, 0},
            {0, 1, 1} 
        }
    );

    orangesRotting(x =
        {
            { 2, 1, 1 },
            { 0, 1, 1 },
            { 1, 0, 1 }
        }
    );
    orangesRotting(x =
        {
            {0, 2}
        }
    );
    orangesRotting(x =
        {
            { 1, 1, 1 },
            { 0, 0, 1 },
            { 1, 0, 1 }
        }
    );

    isCyclic_DirectedGraph(
        4,
        {
            {1},
            {2},
            {3},
            {3}
        }
    );

    isCyclic_DirectedGraph(
        4,
        {
            {1, 3},
            {2},
            {3},
            {2}
        }
    );

    isCyclic_DirectedGraph(
        4,
        {
            {},
            {2},
            {3},
            {2}
        }
    );

    isCyclic_DirectedGraph(
        3,
        {
            {1},
            {2},
            {}
        }
    );

    isCyclic_DirectedGraph(
        1,
        {
            {0}
        }
    );

    isCyclic_DirectedGraph(
        2,
        {
            {1},
            {0}
        }
    );*/

    isCycle_UnDirectedGraph(
        5,
        {
/*0*/       {1},
/*1*/       {0, 2, 4},
/*2*/       {1, 3},
/*3*/       {2, 4},
/*4*/       {1, 3},
        }
    );

    isCycle_UnDirectedGraph(
        4,
        {
            {},
            {2},
            {1, 3},
            {2}
        }
    );

    isCycle_UnDirectedGraph(
        4,
        {
            {2},
            {2},
            {0, 1, 3},
            {2}
        }
    );

    /*
    * https://leetcode.com/problems/walls-and-gates/
    * https://leetcode.com/problems/detonate-the-maximum-bombs/
    * https://leetcode.com/problems/find-eventual-safe-states/
    * https://leetcode.com/problems/escape-the-spreading-fire/
    * https://www.hackerrank.com/challenges/torque-and-development/problem?isFullScreen=true
    * https://www.hackerrank.com/domains/algorithms?filters%5Bsubdomains%5D%5B%5D=graph-theory&filters%5Bdifficulty%5D%5B%5D=medium
    * https://leetcode.com/problems/redundant-connection-ii/
    * https://leetcode.com/problems/redundant-connection/
    */
}