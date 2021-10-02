module PE3 where

data Cell = SpaceCraft Int | Sand | Rock Int | Pit deriving (Eq, Read, Show)

type Grid = [[Cell]]
type Coordinate = (Int, Int)

data Move = North | East | South | West | PickUp | PutDown deriving (Eq, Read, Show)

data Robot = Robot { name :: String,
                     location :: Coordinate,
                     capacity :: Int,
                     energy :: Int,
                     storage :: Int } deriving (Read, Show)

-------------------------------------------------------------------------------------------
--------------------------------- DO NOT CHANGE ABOVE -------------------------------------
------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
-------------------------------------------------------------------------------------------
-------------------------------------- PART I ---------------------------------------------

isInGrid :: Grid -> Coordinate -> Bool
isInGrid grid coor
    | (fst coor < 0) || (snd coor < 0) = False
    | (length (head grid) > (fst coor)) && ((length grid) > (snd coor)) = True
    | otherwise = False

-------------------------------------------------------------------------------------------

totalCount :: Grid -> Int
totalCount grid = countHelper grid 0 (length (head grid)) (length grid)

countHelper grid y lx ly
    | (y < ly) = (countInRow (grid!!y) 0 lx) + (countHelper grid (y+1) lx ly)
    | otherwise = 0

countInRow row x lx
    | (x < lx) = (checkCount (row!!x)) + (countInRow row (x+1) lx)
    | otherwise = 0

checkCount (Rock x) = x
checkCount _ = 0 

-------------------------------------------------------------------------------------------

coordinatesOfPits :: Grid -> [Coordinate]
coordinatesOfPits grid = pitTraverseX grid 0 (length (head grid)) (length grid)

pitTraverseX :: [[Cell]] -> Int -> Int -> Int -> [(Int,Int)]
pitTraverseX grid x lx ly 
        | (x < lx) = (pitTraverseY grid x 0 lx ly) ++ (pitTraverseX grid (x+1) lx ly)
        | otherwise = []

pitTraverseY :: [[Cell]] -> Int -> Int -> Int -> Int -> [(Int,Int)]
pitTraverseY grid x y lx ly
        | (y < ly) = (checkPit x y ((grid!!y)!!x)) ++ (pitTraverseY grid x (y+1) lx ly)
        | otherwise = []

checkPit x y Pit = [(x,y)]
checkPit x y _ = []
-------------------------------------------------------------------------------------------

tracePath :: Grid -> Robot -> [Move] -> [Coordinate]
tracePath grid robot moves = traceHelper grid (location robot) (energy robot) moves False

traceHelper :: Grid -> (Int,Int) -> Int -> [Move] -> Bool -> [(Int,Int)]
traceHelper _ coor _ moves True = [coor| x <- moves]
traceHelper grid coor energy moves False
    | (isPit grid coor) = [coor] ++ (traceHelper grid coor energy (tail moves) True)
    | (energy < 1) = [coor] ++ (traceHelper grid coor energy (tail moves) True)
    | (moves == []) = []
    | otherwise = case (head moves) of
                    (North) -> if isInGrid grid (fst coor, (snd coor) -1) then
                                                                [(fst coor, (snd coor) -1)] ++ (traceHelper grid (fst coor, (snd coor) -1) (energy-1) (tail moves) False) else
                                                                [coor] ++ (traceHelper grid coor (energy - 1) (tail moves) False)
                    (South) -> if isInGrid grid (fst coor, (snd coor) +1) then
                                                                [(fst coor, (snd coor) +1)] ++ (traceHelper grid (fst coor, (snd coor) +1) (energy-1) (tail moves) False) else
                                                                [coor] ++ (traceHelper grid coor (energy - 1) (tail moves) False)
                    (West) -> if isInGrid grid ((fst coor) -1, snd coor) then
                                                                [((fst coor) -1, snd coor)] ++ (traceHelper grid ((fst coor) -1, snd coor) (energy-1) (tail moves) False) else
                                                                [coor] ++ (traceHelper grid coor (energy - 1) (tail moves) False)
                    (East) -> if isInGrid grid ((fst coor) +1, snd coor) then
                                                                [((fst coor) +1, snd coor)] ++ (traceHelper grid ((fst coor) +1, snd coor) (energy-1) (tail moves) False) else
                                                                [coor] ++ (traceHelper grid coor (energy - 1) (tail moves) False)
                    (PickUp) -> if energy <= 5 then
                                            [coor] ++ (traceHelper grid coor 0 (tail moves) True) else
                                            [coor] ++ (traceHelper grid coor (energy - 5) (tail moves) False)
                    (PutDown) -> if energy <= 3 then
                                            [coor] ++ (traceHelper grid coor 0 (tail moves) True) else
                                            [coor] ++ (traceHelper grid coor (energy - 3) (tail moves) False)

isPit grid coor = elem coor (coordinatesOfPits grid)
------------------------------------- PART II ----------------------------------------------

energiseRobots :: Grid -> [Robot] -> [Robot]
energiseRobots grid robots = energiseHelper (head (craftFinderY grid 0 (length (head grid)) (length grid))) robots

craftFinderY :: Grid -> Int -> Int -> Int -> [(Int,Int)]
craftFinderY grid y lx ly
    | (y < ly) = (craftFinderX (grid!!y) 0 y lx) ++ (craftFinderY grid (y+1) lx ly)
    | otherwise = []

craftFinderX :: [Cell] -> Int -> Int -> Int -> [(Int,Int)]
craftFinderX row x y lx
    | ((x < lx) && (isCraft (row!!x))) = [(x,y)]
    | (x < lx) = (craftFinderX row (x+1) y lx)
    | otherwise = []

isCraft (SpaceCraft z) = True
isCraft _ = False

energiseHelper (x,y) robots = [modify x y robot | robot <- robots]

modify x y robot = if (calculate x y robot) <= 100 then
                                                    robot{energy = (calculate x y robot)} else
                                                    robot{energy = 100}

calculate x y robot = (energy robot) + max 0 (100 - (abs(fst (location robot) - x) + abs(snd(location robot) -y) )*20)
                                        
-------------------------------------------------------------------------------------------

applyMoves :: Grid -> Robot -> [Move] -> (Grid, Robot)
applyMoves grid robot moves = applyHelper grid (head (craftFinderY grid 0 (length (head grid)) (length grid))) robot moves

applyHelper grid (x,y) robot moves
            | (moves) == [] = (grid,robot)
            | (energy robot < 1) = (grid,robot)
            | otherwise = case (head moves) of
                                    (North) -> if isPit grid (location robot) then
                                                    applyHelper grid (x,y) robot{energy = (energy robot -1)} (tail moves) else
                                                    applyHelper grid (x,y) (moveHelper grid robot (-1) "v") (tail moves)
                                    (South) -> if isPit grid (location robot) then
                                                    applyHelper grid (x,y) robot{energy = (energy robot -1)} (tail moves) else
                                                    applyHelper grid (x,y) (moveHelper grid robot (1) "v") (tail moves)
                                    (West) -> if isPit grid (location robot) then
                                                    applyHelper grid (x,y) robot{energy = (energy robot -1)} (tail moves) else
                                                    applyHelper grid (x,y) (moveHelper grid robot (-1) "h") (tail moves)
                                    (East) -> if isPit grid (location robot) then
                                                    applyHelper grid (x,y) robot{energy = (energy robot -1)} (tail moves) else
                                                    applyHelper grid (x,y) (moveHelper grid robot (1) "h") (tail moves)
                                    (PickUp) -> if (energy robot) < 5 then
                                                    applyHelper grid (x,y) robot{energy = 0} (tail moves) else
                                                    applyHelper (pickGrid grid robot (fst(location robot), snd(location robot))) (x,y) (pickHelper grid robot) (tail moves)
                                    (PutDown) -> if (energy robot) < 3 then
                                                    applyHelper grid (x,y) robot{energy = 0} (tail moves) else
                                                    applyHelper (putGrid grid robot (x,y)) (x,y) (putHelper grid robot) (tail moves)
           
           
isRock (Rock 0) = False           
isRock (Rock x) = True
isRock _ = False



putAndPick (Rock x) = (Rock (x-1))
putAndPick (Rock 0) = (Rock 0)
putAndPick (SpaceCraft x) = (SpaceCraft (x+1))
putAndPick x = x

putGrid grid robot (x,y) = if (location robot == (x,y)) then
                            take y grid ++ [take x (grid!!y) ++ [putAndPick ((grid!!y)!!x)] ++ drop (x + 1) (grid!!y)]
                            ++ drop (y + 1) grid else
                            grid

pickGrid grid robot (x,y) = if isRock((grid!!y)!!x) && ((location robot) == (x,y)) && ((capacity robot) > (storage robot)) then
                            take y grid ++ [take x (grid!!y) ++ [putAndPick ((grid!!y)!!x)] ++ drop (x + 1) (grid!!y)]
                            ++ drop (y + 1) grid else
                            grid
            
putHelper grid robot = if isCraft (grid!!(snd(location robot))!!(fst(location robot))) then
                        robot{energy = (energy robot - 3), storage = (storage robot - 1)} else
                        robot{energy = (energy robot - 3)}
            
pickHelper grid robot = if (isRock (grid!!(snd(location robot))!!(fst(location robot)))) && ((capacity robot) > (storage robot)) then
                        robot{energy = (energy robot - 5), storage = (storage robot + 1)} else
                        robot{energy = (energy robot - 5)}
            
moveHelper grid robot i "v" = if isInGrid grid (fst (location robot), snd(location robot) + i) then
                                    robot{energy = (energy robot - 1), location = (fst (location robot), snd(location robot) + i)} else
                                    robot{energy = (energy robot -1)}
                                    
moveHelper grid robot i "h" = if isInGrid grid (fst (location robot) + i, snd(location robot)) then
                                    robot{energy = (energy robot - 1), location = (fst (location robot) + i, snd(location robot))} else
                                    robot{energy = (energy robot -1)}

