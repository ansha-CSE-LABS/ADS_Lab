graph = [[1, 1, 0, 0, 0],
         [0, 1, 0, 0, 1],
         [1, 0, 0, 1, 1],
         [0, 0, 0, 0, 0],
         [1, 0, 1, 0, 1]]
m =len(graph)
n =len(graph[0])

visit=set()
count=0

def dfs(i,j):
    if i>=m or j>=n or i<0 or j<0 or graph[i][j]==0:
        return
    if (i,j) in visit:
        return
    
    if graph[i][j]==1:
        visit.add((i,j))
        # + neighbours
        dfs(i,j+1)
        dfs(i+1,j)
        dfs(i,j-1)
        dfs(i-1,j)
        # x neighbours
        dfs(i-1,j-1)
        dfs(i+1,j+1)
        dfs(i-1,j+1)
        dfs(i+1,j-1)

for i in range(m):
    for j in range(n):
        if graph[i][j]==1 and (i,j) not in visit:
            dfs(i,j)
            count+=1

print(count)
