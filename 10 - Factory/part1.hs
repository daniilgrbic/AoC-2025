import Data.List.Split (splitOn)

type Diagram = [Bool]

type Button = [Int]

pressButton :: Diagram -> Button -> Diagram
pressButton diagram button =
  [ if idx `elem` button then not light else light
    | (light, idx) <- zip diagram [0 ..]
  ]

bfs :: [Diagram] -> [Button] -> Diagram -> Int
bfs diagrams buttons target =
    if target `elem` diagrams
    then 0
    else 1 + bfs [pressButton d b | d <- diagrams, b <- buttons] buttons target

startMachine :: String -> IO Int
startMachine line = do
  let diagram :: Diagram = [x | ch <- (tail . init . head . words) line, let x = ch == '#']
  let buttons :: [Button] = (map (map read . splitOn "," . tail . init) . tail . init . words) line
  print diagram
  print buttons

  let steps = bfs [[False | _ <- [1..(length diagram)]]] buttons diagram
  print steps

  return steps

main :: IO ()
main = do
  contents <- getContents
  results <- mapM startMachine (lines contents)
  print (sum results)
