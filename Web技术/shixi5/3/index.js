class animal{	
	constructor(color,age)
	{
		this.age = age
		this.color = color
		this.type = '无'
	}
	
	eat()
	{
		console.log(`吃东西`)
	}
	sport()
	{
		console.log(`在运动`)
	}
}

class cat extends animal
{
	constructor(color,age,name,characteristic)
	{
		super(color,age)
		this.type = 'cat'
		this.name = name
		this.characteristic = characteristic
	}
	work()
	{
		console.log(`${this.name}在捉老鼠`)
	}
	sleep()
	{
		console.log(`${this.name}在睡觉`)
	}
}

let cat1 = new cat('red',4,'c1','胖')
let cat2 = new cat('white',2,'c2','瘦')
let cat3 = new cat('blue',6,'c3','懒')

cat1.eat()
cat2.work()
cat3.sleep()
