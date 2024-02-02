class Timer
{
	constructor(wait)
	{
		this.wait = wait
		this.num = 0
	}
	
	start()
	{
		return new Promise((resolve,reject)=>
		{
			this.num = setInterval(()=>{
				resolve()	
			},this.wait)
		})
	}
	
	cancel()
	{
		clearInterval(this.num)
	}
}

const timer = new Timer(3000)
//timer.start().then(()=> console.log('时间到！'))
timer.cancel()
