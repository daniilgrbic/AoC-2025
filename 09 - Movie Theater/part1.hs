import Control.Monad (forM_)
import Data.List.Split (splitOn)

pairs :: [a] -> [(a, a)]
pairs [] = []
pairs (x : xs) = [(x, y) | y <- xs] ++ pairs xs

area :: ([Int], [Int]) -> Int
area ([x1, y1], [x2, y2]) = (abs (x2 - x1) + 1) * (abs (y2 - y1) + 1)

main :: IO ()
main = do
  contents <- getContents
  let points :: [[Int]] = map (map read . splitOn ",") (lines contents)

  -- forM_ (pairs points) $ \pair -> do
  --     putStrLn (show pair ++ " -> " ++ show (area pair))

  print (maximum (map area (pairs points)))
