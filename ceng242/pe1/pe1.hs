module PE1 where

import Text.Printf


-- This function takes a Double and rounds it to 2 decimal places as requested in the PE --
getRounded :: Double -> Double
getRounded x = read s :: Double
               where s = printf "%.2f" x

-------------------------------------------------------------------------------------------
----------------------- DO NOT CHANGE ABOVE OR FUNCTION SIGNATURES-------------------------
------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
-------------------------------------------------------------------------------------------

convertTL :: Double -> String -> Double
convertTL money "USD" = getRounded (money / 8.18)
convertTL money "EUR" = getRounded (money / 9.62)
convertTL money "BTC" = getRounded (money / 473497.31)

-------------------------------------------------------------------------------------------

countOnWatch :: [String] -> String -> Int -> Int
countOnWatch schedule employee days = length [x | x <- (take days schedule), x == employee]

-------------------------------------------------------------------------------------------

encrypt :: Int -> Int
encrypt x = helper (parse [x])

parse x
    | (head x < 10) = x
    | otherwise = parse ((head x `div` 10):(head x `mod` 10):(tail x))
    
helper [x,y,z,t] = (process x) * 1000 + (process y) * 100 + (process z) * 10 + process t

process digit 
    | (digit `mod` 3) == 0 = digit - 1
    | (digit `mod` 4) == 0 = if digit == 4 then 8 else 6
    | (digit `mod` 5) == 0 = digit + 3
    | digit == 7 = 1
    | otherwise = digit + 4

-------------------------------------------------------------------------------------------

compoundInterests :: [(Double, Int)] -> [Double]
compoundInterests investments = [(invest x) | x <- investments]

invest :: (Double, Int) -> Double
invest (money,year)
    | money > 10000 = if (year < 2) then (calculate money 0.105 year) else (calculate money 0.115 year)
    | money < 10000 = if (year < 2) then (calculate money 0.09 year) else (calculate money 0.095 year)

calculate :: Double -> Double -> Int -> Double
calculate p r n = getRounded (p * (1 + (r/12))^(n*12))








