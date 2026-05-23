@echo off
echo. > results.txt
del out*.dot 2>nul

echo. >> results.txt
echo 1. Valid X can win in top row, next X >> results.txt
../tic_tac_toe.exe test01.txt out01.dot >> results.txt 2>&1
type out01.dot >> results.txt 2>nul

echo. >> results.txt
echo 2. Valid O has a threat, next O >> results.txt
../tic_tac_toe.exe test02.txt out02.dot >> results.txt 2>&1
type out02.dot >> results.txt 2>nul

echo. >> results.txt
echo 3. Valid middle game 1, strategy X, next X >> results.txt
../tic_tac_toe.exe test03.txt out03.dot >> results.txt 2>&1
type out03.dot >> results.txt 2>nul

echo. >> results.txt
echo 4. Valid middle game 2, strategy O, next O >> results.txt
../tic_tac_toe.exe test04.txt out04.dot >> results.txt 2>&1
type out04.dot >> results.txt 2>nul

echo. >> results.txt
echo 5. Valid middle game 3, strategy X, next X >> results.txt
../tic_tac_toe.exe test05.txt out05.dot >> results.txt 2>&1
type out05.dot >> results.txt 2>nul

echo. >> results.txt
echo 6. Valid terminal X win >> results.txt
../tic_tac_toe.exe test06.txt out06.dot >> results.txt 2>&1
type out06.dot >> results.txt 2>nul

echo. >> results.txt
echo 7. Valid terminal O win >> results.txt
../tic_tac_toe.exe test07.txt out07.dot >> results.txt 2>&1
type out07.dot >> results.txt 2>nul

echo. >> results.txt
echo 8. Valid full board draw >> results.txt
../tic_tac_toe.exe test08.txt out08.dot >> results.txt 2>&1
type out08.dot >> results.txt 2>nul

echo. >> results.txt
echo 9. Valid defensive position, next X >> results.txt
../tic_tac_toe.exe test09.txt out09.dot >> results.txt 2>&1
type out09.dot >> results.txt 2>nul

echo. >> results.txt
echo 10. Valid fork-like position, next X >> results.txt
../tic_tac_toe.exe test10.txt out10.dot >> results.txt 2>&1
type out10.dot >> results.txt 2>nul

echo. >> results.txt
echo 11. Valid top row blocked, next X >> results.txt
../tic_tac_toe.exe test11.txt out11.dot >> results.txt 2>&1
type out11.dot >> results.txt 2>nul

echo. >> results.txt
echo 12. Valid vertical threat, next X >> results.txt
../tic_tac_toe.exe test12.txt out12.dot >> results.txt 2>&1
type out12.dot >> results.txt 2>nul

echo. >> results.txt
echo 13. Valid scattered position, next X >> results.txt
../tic_tac_toe.exe test13.txt out13.dot >> results.txt 2>&1
type out13.dot >> results.txt 2>nul

echo. >> results.txt
echo 14. Valid almost middle game, next O >> results.txt
../tic_tac_toe.exe test14.txt out14.dot >> results.txt 2>&1
type out14.dot >> results.txt 2>nul

echo. >> results.txt
echo 15. Invalid empty input file >> results.txt
../tic_tac_toe.exe test15.txt out15.dot >> results.txt 2>&1
type out15.dot >> results.txt 2>nul

echo. >> results.txt
echo 16. Invalid missing required line >> results.txt
../tic_tac_toe.exe test16.txt out16.dot >> results.txt 2>&1
type out16.dot >> results.txt 2>nul

echo. >> results.txt
echo 17. Invalid extra line >> results.txt
../tic_tac_toe.exe test17.txt out17.dot >> results.txt 2>&1
type out17.dot >> results.txt 2>nul

echo. >> results.txt
echo 18. Invalid first board row is too long >> results.txt
../tic_tac_toe.exe test18.txt out18.dot >> results.txt 2>&1
type out18.dot >> results.txt 2>nul

echo. >> results.txt
echo 19. Invalid second board row is too short >> results.txt
../tic_tac_toe.exe test19.txt out19.dot >> results.txt 2>&1
type out19.dot >> results.txt 2>nul

echo. >> results.txt
echo 20. Invalid board symbol >> results.txt
../tic_tac_toe.exe test20.txt out20.dot >> results.txt 2>&1
type out20.dot >> results.txt 2>nul

echo. >> results.txt
echo 21. Invalid strategy player >> results.txt
../tic_tac_toe.exe test21.txt out21.dot >> results.txt 2>&1
type out21.dot >> results.txt 2>nul

echo. >> results.txt
echo 22. Invalid next player >> results.txt
../tic_tac_toe.exe test22.txt out22.dot >> results.txt 2>&1
type out22.dot >> results.txt 2>nul

echo. >> results.txt
echo 23. Invalid too many X marks >> results.txt
../tic_tac_toe.exe test23.txt out23.dot >> results.txt 2>&1
type out23.dot >> results.txt 2>nul

echo. >> results.txt
echo 24. Invalid too many O marks >> results.txt
../tic_tac_toe.exe test24.txt out24.dot >> results.txt 2>&1
type out24.dot >> results.txt 2>nul

echo. >> results.txt
echo 25. Invalid both players win >> results.txt
../tic_tac_toe.exe test25.txt out25.dot >> results.txt 2>&1
type out25.dot >> results.txt 2>nul

echo. >> results.txt
echo 26. Invalid next player for equal counts >> results.txt
../tic_tac_toe.exe test26.txt out26.dot >> results.txt 2>&1
type out26.dot >> results.txt 2>nul

echo. >> results.txt
echo 27. Valid empty board, strategy X, next X >> results.txt
../tic_tac_toe.exe test27.txt out27.dot >> results.txt 2>&1
type out27.dot >> results.txt 2>nul

echo. >> results.txt
echo 28. Valid first move in corner, strategy O, next O >> results.txt
../tic_tac_toe.exe test28.txt out28.dot >> results.txt 2>&1
type out28.dot >> results.txt 2>nul

echo. >> results.txt
echo 29. Valid first move in center, strategy X, next O >> results.txt
../tic_tac_toe.exe test29.txt out29.dot >> results.txt 2>&1
type out29.dot >> results.txt 2>nul

echo. >> results.txt
echo 30. Valid one X and one O, next X >> results.txt
../tic_tac_toe.exe test30.txt out30.dot >> results.txt 2>&1
type out30.dot >> results.txt 2>nul

echo Done. See results.txt
