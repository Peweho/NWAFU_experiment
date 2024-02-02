function randomNum(ban) {
	let ch
	do {
		ch = Math.floor(Math.random() * 10).toString()
	} while (ban.search(ch) >= 0)

	return ch

}
function randomChar(ban, t) {
	let bios = 0

	if (t.charCodeAt() >= 65 && t.charCodeAt() <= 90)
		bios = 65
	else
		bios = 97

	let ch
	do {
		ch = String.fromCharCode(Math.floor(Math.random() * 26) + bios)
	} while (ban.search(ch) >= 0)
	return ch
}

function isChar(ban,ch)
{
	for(const sh in ban)
	{
		if(sh === ch)
			return true
	}
	
	return false
}

function randomElse(ban, target) {
	let ch
	do {
		ch = target[Math.floor(Math.random() * target.length)]
	} while (isChar(ban,ch))
	return ch
}


	let button = document.getElementsByClassName("button")[0]
	
	button.addEventListener('click', function () {
	let useChar = document.getElementsByClassName("checkbox")
	for(let k=0;k<useChar.length;++k)
	{
		if(useChar[k].checked === true)
			break;
			
		if(k + 1 === useChar.length)
		{
			alert("请至少选择一种字符")
			return;
		}
	}
	let addtion = document.getElementsByClassName("additional")[0].value
	let ban = ''
	
	let elseChar = document.getElementsByClassName("elsechar")[0]
	if(elseChar.checked === true)
		ban = document.getElementsByClassName("ban")[0].value
		
	let pwdLength = document.getElementsByClassName("lenght")[0].value
	let pwdCount = document.getElementsByClassName("count")[0].value
	let input = document.getElementsByClassName("textArea")[0]
	let pwd = ""
	console.log(pwdLength)
	console.log(pwdCount)
	for (let i = 0; i < pwdCount; ++i) {
		
		for (let j = 0; j < pwdLength; ++j) {
			let pos = 0
			do {
				pos = Math.floor(Math.random() * useChar.length)
			} while (useChar[pos].checked === false)

			switch (pos) {
				case 0: pwd += randomChar(ban, 'a'); break;
				case 1: pwd += randomChar(ban, 'A'); break;
				case 2: pwd += randomNum(ban); break;
				case 3: pwd += randomElse(ban, addtion); break;
			}
		}
		pwd += "\n"
	}
	input.innerHTML = pwd
})