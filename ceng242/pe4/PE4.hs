module PE4 where

import Data.Maybe -- up to you if you want to use it or not

-- Generic DictTree definition with two type arguments
data DictTree k v = Node [(k, DictTree k v)] | Leaf v deriving Show

-- Lightweight Char wrapper as a 'safe' Digit type
newtype Digit = Digit Char deriving (Show, Eq, Ord) -- derive equality and comparison too!

-- Type aliases
type DigitTree = DictTree Digit String
type PhoneNumber = [Digit]


---------------------------------------------------------------------------------------------
------------------------- DO NOT CHANGE ABOVE OR FUNCTION SIGNATURES-------------------------
--------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
--------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
---------------------------------------------------------------------------------------------


----------
-- Part I:
-- Some Maybe fun! Basic practice with an existing custom datatype.

-- toDigit: Safely convert a character to a digit
toDigit :: Char -> Maybe Digit
toDigit x 
        | (x >= '0') && (x <= '9') = Just (Digit x)
        | otherwise = Nothing

-- toDigits: Safely convert a bunch of characters to a list of digits.
--           Particularly, an empty string should fail.
toDigits :: String -> Maybe PhoneNumber
toDigits "" = Nothing
toDigits str = if (check str) then (Just [(Digit x) | x <- str]) else Nothing

check str = if ([x | x <- str, (x < '0') || (x > '9')] == []) then True else False

-----------
-- Part II:
-- Some phonebook business.

-- numContacts: Count the number of contacts in the phonebook...
numContacts :: DigitTree -> Int
numContacts tree = numHelper tree

numHelper :: DigitTree -> Int
numHelper (Leaf x) = 1
numHelper (Node x) = 0 + helperTwo x

helperTwo :: [(Digit,DigitTree)] -> Int
helperTwo x 
    | (ifEmpty x) = 0
    | otherwise = (numHelper (snd (head x))) + (helperTwo (tail x))
    
ifEmpty [] = True
ifEmpty x = False

-- getContacts: Generate the contacts and their phone numbers in order given a tree. 
getContacts :: DigitTree -> [(PhoneNumber, String)]
getContacts tree = getHelper [] tree

getHelper k (Leaf x) = [(k,x)]
getHelper k (Node x) = [] ++ (helperRec k x)

helperRec k x
    | (ifEmpty x) = []
    | otherwise = (getHelper (k ++ [fst(head x)]) (snd(head x))) ++ (helperRec k (tail x))
 
-- autocomplete: Create an autocomplete list of contacts given a prefix
-- e.g. autocomplete "32" areaCodes -> 
--      [([Digit '2'], "Adana"), ([Digit '6'], "Hatay"), ([Digit '8'], "Osmaniye")]
autocomplete :: String -> DigitTree -> [(PhoneNumber, String)]
autocomplete "" _ = []
autocomplete str tree = if (toDigits str) /= Nothing then autoHelper (justToNormal (toDigits str)) tree else []

autoHelper [] (Leaf x) = [([],x)]
autoHelper k (Leaf x) = []
autoHelper [] (Node x) = getContacts (Node x)
autoHelper k (Node x) = [] ++ autoRec k x

autoRec k x
    | (ifEmpty x) = []
    | (fst(head x) == ((head k))) = autoHelper (tail k) (snd (head x))
    | otherwise = autoRec k (tail x)
    
justToNormal (Just x) = x

-----------
-- Example Trees
-- Two example trees to play around with, including THE exampleTree from the text. 
-- Feel free to delete these or change their names or whatever!

exampleTree :: DigitTree
exampleTree = Node [
    (Digit '1', Node [
        (Digit '3', Node [
            (Digit '7', Node [
                (Digit '8', Leaf "Jones")])]),
        (Digit '5', Leaf "Steele"),
        (Digit '9', Node [
            (Digit '1', Leaf "Marlow"),
            (Digit '2', Node [
                (Digit '3', Leaf "Stewart")])])]),
    (Digit '3', Leaf "Church"),
    (Digit '7', Node [
        (Digit '2', Leaf "Curry"),
        (Digit '7', Leaf "Hughes")])]

areaCodes :: DigitTree
areaCodes = Node [
    (Digit '3', Node [
        (Digit '1', Node [
            (Digit '2', Leaf "Ankara")]),
        (Digit '2', Node [
            (Digit '2', Leaf "Adana"),
            (Digit '6', Leaf "Hatay"),
            (Digit '8', Leaf "Osmaniye")])]),
    (Digit '4', Node [
        (Digit '6', Node [
            (Digit '6', Leaf "Artvin")])])]

