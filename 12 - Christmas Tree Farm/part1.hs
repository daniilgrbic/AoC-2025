import Data.Char (GeneralCategory (DecimalNumber), isSpace)
import Data.List.Split (splitOn)
import Text.Printf (printf)

-- splitBlocks ["1", " ", "2", "3"] -> [["1"], ["2", "3"]]
splitBlocks :: [String] -> [[String]]
splitBlocks [] = []
splitBlocks xs =
  let (block, remainder) = break (all isSpace) xs
      remainder' = dropWhile (all isSpace) remainder
   in block : splitBlocks remainder'

-- linspace 0 1 5 -> [0.0,0.2,0.4,0.6,0.8,1.0]
linspace :: Float -> Float -> Int -> [Float]
linspace a b n =
  [a + (b - a) * fromIntegral i / fromIntegral n | i <- [0 .. n]]

solve :: Float -> String -> Bool
solve ratio line = do
  let [rows, cols] :: [Float] =
        (map read . splitOn "x" . init . head . words) line
  let count :: Float = (sum . map read . tail . words) line
  (count * 7) / (rows * cols) <= ratio 

main :: IO ()
main = do
  contents <- getContents

  let groups = (splitBlocks . lines) contents
  let testCases = groups !! 6

  let ratios = linspace (7/9) 1 10
  let runs =
        [ (ratio, answer)
          | ratio <- ratios,
            let caseAnswers = map (solve ratio) testCases,
            let answer = (length . filter id) caseAnswers
        ]

  mapM_ print runs
