auto a = "global";

{
    fun showA()
    {
        print(a);
    }

    showA();
    auto a = "local";
    showA();
}