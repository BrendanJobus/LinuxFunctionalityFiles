import System.Environment
import Data.Char

main = do
      weight <- getLine
      -- First combine it to one line, then try to make it freepoint
      putStrLn $ if (sum $ [digitToInt x | x <- weight]) `mod` 2 == 0 then "YES" else "NO"

      --let w = sum $ [digitToInt x | x <- weight]
      --putStrLn $ if w `mod` 2 == 0 then "YES" else "NO"
