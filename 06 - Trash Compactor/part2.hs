import Data.Char (isSpace)
import Data.List (transpose)

-- splitBlocks ["1", " ", "2", "3"] -> [["1"], ["2", "3"]]
splitBlocks :: [String] -> [[String]]
splitBlocks [] = []
splitBlocks xs =
  let (block, remainder) = break (all isSpace) xs
      remainder' = dropWhile (all isSpace) remainder
   in block : splitBlocks remainder'

applyOp :: String -> [Int] -> Int
applyOp "+" = sum
applyOp "*" = product

main :: IO ()
main = do
  file <- getContents

  let allLines = lines file
  let numberLines = init allLines
  let opLines = words (last allLines)

  let transposedLines = transpose numberLines
  --   putStrLn ("Transposed lines: " ++ show transposedLines)

  let blocks = map (map read) (splitBlocks transposedLines)
  --   putStrLn ("Blocks: " ++ show blocks)

  let answers = zipWith applyOp opLines blocks
  --   putStrLn ("Answers: " ++ show answers)

  putStrLn ("Total sum: " ++ show (sum answers))
