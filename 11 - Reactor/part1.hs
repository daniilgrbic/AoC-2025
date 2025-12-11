import Data.Map qualified as Map

type Connection = (String, String)

type Graph = Map.Map String [String]

generateConnections :: String -> [Connection]
generateConnections entry = do
  let node = (init . head . words) entry
  let next = (tail . words) entry
  map (node,) next

buildGraph :: [Connection] -> Graph
buildGraph = foldr (\(u, v) -> Map.insertWith (++) u [v]) Map.empty

dfs :: Graph -> String -> String -> Int
dfs graph node target =
  if target == node
    then 1
    else sum [dfs graph next target | next <- graph Map.! node]

main :: IO ()
main = do
  contents <- getContents

  let connections = concatMap generateConnections (lines contents)
  let graph = buildGraph connections

  print graph
  print (dfs graph "you" "out")
