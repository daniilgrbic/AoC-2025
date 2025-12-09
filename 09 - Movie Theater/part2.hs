import Data.List (sortBy)
import Data.List.Split (splitOn)
import Data.Ord (compare)

pairs :: [a] -> [(a, a)]
pairs [x] = []
pairs (x : xs) = (x, head xs) : pairs xs

cartesian :: [a] -> [(a, a)]
cartesian [] = []
cartesian (x : xs) = [(x, y) | y <- xs] ++ cartesian xs

area :: ((Int, Int), (Int, Int)) -> Int
area ((x1, y1), (x2, y2)) = (abs (x2 - x1) + 1) * (abs (y2 - y1) + 1)

-- Reorder rect points to be bottom left and top right
orderRect :: ((Int, Int), (Int, Int)) -> ((Int, Int), (Int, Int))
orderRect ((x1, y1), (x2, y2)) =
  ((min x1 x2, min y1 y2), (max x1 x2, max y1 y2))

main :: IO ()
main = do
  contents <- getContents
  let points = map ((\[a, b] -> (a, b)) . map read . splitOn ",") (lines contents)

  -- Build edges = [(pt, dir@(dx, dy))]
  let edges =
        [ (pt, (x2 - x1, y2 - y1))
          | (pt@(x1, y1), (x2, y2)) <- pairs (points ++ [head points])
        ]

  -- Horizontal edges, normalize direction to positive x, sorted by length
  let horizontalEdges =
        [ if dx > 0
            then (p1, (dx, 0))
            else ((fst p1 + dx, snd p1), (-dx, 0))
          | (p1, (dx, dy)) <- edges,
            dy == 0
        ]
  let sortedHorizontalEdges =
        sortBy
          (\(_, (dx1, _)) (_, (dx2, _)) -> compare dx2 dx1)
          horizontalEdges

  -- Vertical edges, normalize direction to positive y, sorted by length
  let verticalEdges =
        [ if dy > 0
            then (p1, (0, dy))
            else ((fst p1, snd p1 + dy), (0, -dy))
          | (p1, (dx, dy)) <- edges,
            dx == 0
        ]
  let sortedVerticalEdges =
        sortBy
          (\(_, (_, dy1)) (_, (_, dy2)) -> compare dy2 dy1)
          verticalEdges

  -- All rectangles, sorted by area in descending order
  let rectangles = cartesian points
  let sortedRects = sortBy (\a b -> compare (area b) (area a)) rectangles

  -- Compute maximum rectangle area by dropping invalid rects, and taking first good one.
  -- Since rectangles are already sorted, the first we find is the answer!
  let result =
          take
          1
          [ area rect
            | (p1@(x1, y1), p2@(x2, y2)) <- sortedRects,
              let ((a1, b1), (a2, b2)) = orderRect (p1, p2),
              let intersectsRect =
                    or
                      [ p0 + dx > a1 && p0 < a2 && py > b1 && py < b2
                        | ((px, py), (dx, _)) <- sortedHorizontalEdges,
                          let p0 = px
                      ]
                      || or
                        [ p0 + dy > b1 && p0 < b2 && px > a1 && px < a2
                          | ((px, py), (_, dy)) <- sortedVerticalEdges,
                            let p0 = py
                        ],
              not intersectsRect,
              let rect = ((x1, y1), (x2, y2))
          ]

  print (head result)
