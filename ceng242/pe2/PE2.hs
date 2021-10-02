module PE2 where

---------------------------------------------------------------------------------------------
------------------------- DO NOT CHANGE ABOVE OR FUNCTION SIGNATURES-------------------------
--------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
--------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
---------------------------------------------------------------------------------------------

-- Note: undefined is a value that causes an error when evaluated. Replace it with
-- a viable definition! Name your arguments as you like by changing the holes: _

--------------------------
-- Part I: Time to inf up!

-- naturals: The infinite list of natural numbers. That's it!
naturals :: [Integer]
naturals = [0..]

-- interleave: Interleave two lists, cutting off on the shorter list.
interleave :: [a] -> [a] -> [a]
interleave [] _ = []
interleave _ [] = []
interleave x y = (head x):(head y):(interleave (tail x) (tail y))

-- integers: The infinite list of integers. Ordered as [0, -1, 1, -2, 2, -3, 3, -4, 4...].
integers :: [Integer]
integers = interleave [0..] [-1,-2..]

--------------------------------
-- Part II: SJSON Prettification

-- splitOn: Split string on first occurence of character.
splitOn :: Char -> String -> (String, String)
splitOn ch str = splitHelper ch ("",str)

splitHelper ch (str1, str2) 
    | str2 == "" = (str1, str2)
    | (head str2) == ch = (str1, tail str2)
    | otherwise = splitHelper ch (str1 ++ [(head str2)], tail str2)

-- tokenizeS: Transform an SJSON string into a list of tokens.
tokenizeS :: String -> [String]
tokenizeS x = tokenHelper ([], x) ""

tokenHelper (arr, str) tmp
    | str == "" = arr
    | ((head str) == ' ') || ((head str) == '\t') || ((head str) == '\n') = if tmp == "" then tokenHelper (arr,tail str) tmp else tokenHelper (arr, tail str) (tmp ++ [(head str)])
    | (head str) == '\'' = tokenHelper (arr ++ [fst(splitOn '\'' (tail str))], snd(splitOn '\'' (tail str))) ""
    | ((head str) == '{') || ((head str) == '}') || ((head str) == ',') || ((head str) == ':') = if tmp == "" then
                                                                                                    tokenHelper (arr ++ [[(head str)]], tail str) "" else
                                                                                                    tokenHelper (arr ++ [tmp] ++ [[(head str)]], tail str) ""
    | otherwise = tokenHelper (arr, tail str) (tmp ++ [(head str)])

-- prettifyS: Prettify SJSON, better tokenize first!
prettifyS :: String -> String
prettifyS str = prettyHelper (tokenizeS str) 0


prettyHelper :: [String] -> Int -> String
prettyHelper [] _ = ""
prettyHelper arr ind
    | (head arr) == "{" = "{\n" ++ (indent (ind+1)) ++ prettyHelper (tail arr) (ind+1)
    | (head arr) == "}" = "\n" ++ (indent (ind -1)) ++ "}" ++ prettyHelper (tail arr) (ind-1) 
    | (head arr) == ":" = ": " ++ prettyHelper (tail arr) ind
    | (head arr) == "," = ",\n" ++ (indent ind) ++ prettyHelper (tail arr) ind
    | otherwise = "\'" ++ (head arr) ++ "\'" ++ prettyHelper (tail arr) ind
    
indent 0 = ""
indent x = "    " ++ indent (x-1)


-- Good luck to you, friend and colleague!

