import Data.List (transpose)

toNums :: String -> [Int]
toNums line = map read (words line)

applyOp :: String -> [Int] -> Int
applyOp "+" = sum
applyOp "*" = product

main :: IO ()
main = do
  file <- getContents

  let allLines = lines file
  let numberLines = map toNums (init allLines)
  let opLines = words (last allLines)

  let numberColumns = transpose numberLines
  let answers = zipWith applyOp opLines numberColumns

  print (sum answers)
