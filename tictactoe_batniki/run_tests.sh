#!/bin/bash
echo "" > results.txt
rm -f out*.dot

echo "" >> results.txt
echo "1. Valid X can win in top row, next X" >> results.txt
../tic_tac_toe test01.txt out01.dot >> results.txt 2>&1
cat out01.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "2. Valid O has a threat, next O" >> results.txt
../tic_tac_toe test02.txt out02.dot >> results.txt 2>&1
cat out02.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "3. Valid middle game 1, strategy X, next X" >> results.txt
../tic_tac_toe test03.txt out03.dot >> results.txt 2>&1
cat out03.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "4. Valid middle game 2, strategy O, next O" >> results.txt
../tic_tac_toe test04.txt out04.dot >> results.txt 2>&1
cat out04.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "5. Valid middle game 3, strategy X, next X" >> results.txt
../tic_tac_toe test05.txt out05.dot >> results.txt 2>&1
cat out05.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "6. Valid terminal X win" >> results.txt
../tic_tac_toe test06.txt out06.dot >> results.txt 2>&1
cat out06.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "7. Valid terminal O win" >> results.txt
../tic_tac_toe test07.txt out07.dot >> results.txt 2>&1
cat out07.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "8. Valid full board draw" >> results.txt
../tic_tac_toe test08.txt out08.dot >> results.txt 2>&1
cat out08.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "9. Valid defensive position, next X" >> results.txt
../tic_tac_toe test09.txt out09.dot >> results.txt 2>&1
cat out09.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "10. Valid fork-like position, next X" >> results.txt
../tic_tac_toe test10.txt out10.dot >> results.txt 2>&1
cat out10.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "11. Valid top row blocked, next X" >> results.txt
../tic_tac_toe test11.txt out11.dot >> results.txt 2>&1
cat out11.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "12. Valid vertical threat, next X" >> results.txt
../tic_tac_toe test12.txt out12.dot >> results.txt 2>&1
cat out12.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "13. Valid scattered position, next X" >> results.txt
../tic_tac_toe test13.txt out13.dot >> results.txt 2>&1
cat out13.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "14. Valid almost middle game, next O" >> results.txt
../tic_tac_toe test14.txt out14.dot >> results.txt 2>&1
cat out14.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "15. Invalid empty input file" >> results.txt
../tic_tac_toe test15.txt out15.dot >> results.txt 2>&1
cat out15.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "16. Invalid missing required line" >> results.txt
../tic_tac_toe test16.txt out16.dot >> results.txt 2>&1
cat out16.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "17. Invalid extra line" >> results.txt
../tic_tac_toe test17.txt out17.dot >> results.txt 2>&1
cat out17.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "18. Invalid first board row is too long" >> results.txt
../tic_tac_toe test18.txt out18.dot >> results.txt 2>&1
cat out18.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "19. Invalid second board row is too short" >> results.txt
../tic_tac_toe test19.txt out19.dot >> results.txt 2>&1
cat out19.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "20. Invalid board symbol" >> results.txt
../tic_tac_toe test20.txt out20.dot >> results.txt 2>&1
cat out20.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "21. Invalid strategy player" >> results.txt
../tic_tac_toe test21.txt out21.dot >> results.txt 2>&1
cat out21.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "22. Invalid next player" >> results.txt
../tic_tac_toe test22.txt out22.dot >> results.txt 2>&1
cat out22.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "23. Invalid too many X marks" >> results.txt
../tic_tac_toe test23.txt out23.dot >> results.txt 2>&1
cat out23.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "24. Invalid too many O marks" >> results.txt
../tic_tac_toe test24.txt out24.dot >> results.txt 2>&1
cat out24.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "25. Invalid both players win" >> results.txt
../tic_tac_toe test25.txt out25.dot >> results.txt 2>&1
cat out25.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "26. Invalid next player for equal counts" >> results.txt
../tic_tac_toe test26.txt out26.dot >> results.txt 2>&1
cat out26.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "27. Valid empty board, strategy X, next X" >> results.txt
../tic_tac_toe test27.txt out27.dot >> results.txt 2>&1
cat out27.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "28. Valid first move in corner, strategy O, next O" >> results.txt
../tic_tac_toe test28.txt out28.dot >> results.txt 2>&1
cat out28.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "29. Valid first move in center, strategy X, next O" >> results.txt
../tic_tac_toe test29.txt out29.dot >> results.txt 2>&1
cat out29.dot >> results.txt 2>/dev/null

echo "" >> results.txt
echo "30. Valid one X and one O, next X" >> results.txt
../tic_tac_toe test30.txt out30.dot >> results.txt 2>&1
cat out30.dot >> results.txt 2>/dev/null

echo "Done. See results.txt"
