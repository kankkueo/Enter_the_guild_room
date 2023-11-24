msg=$(./game | head -1)
if [ "$msg" == "Starting game" ]
then
    echo "GAME START TEST SUCCESS"
else
    echo "GAME START TEST FAIL"
fi
