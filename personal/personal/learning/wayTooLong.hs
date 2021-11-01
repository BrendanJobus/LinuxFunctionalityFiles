import System.Environment
import Data.Char

main = do
  n <- getLine
  let en = sum $ [digitToInt x | x <- n]
  putStrLn $ show [1..n]
