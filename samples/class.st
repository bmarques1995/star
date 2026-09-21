class StarClass
{
	var name#string = "Star";
	StarClass()
	{
	
	}

	fun StarMethod()#string
	{
		return "Olá, Star";
	}
}

var obj = StarClass();
print(obj.StarMethod());