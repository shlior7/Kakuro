const fs = require('fs')
const path = require('path')
const cheerio = require('cheerio');

const fsReadFileHtml = (fileName) => {
  return new Promise((resolve, reject) => {
    fs.readFile(path.join(__dirname, fileName), 'utf8', (error, htmlString) => {
      if (!error && htmlString) {
        resolve(htmlString);
      } else {
        reject(error)
      }
    });
  });
}

fsReadFileHtml("kakuro1.html").then((htmlString) => {
  const $ = cheerio.load(htmlString);
  const kakuro_table_list = $("body > table > tbody > tr").map((index, element1) => {
    return $(element1.children).map((index, element2) => {
      return [$(element2).attr('class'), $(element2).text()]
    });
  });

  const result = []
  kakuro_table_list.each((index, element3) => {
    element3.each((index, element4) => {
      if (element4 !== undefined)
        result.push(element4)

    })
  })
  const res = []
  result.map((element, index) => {
    switch (element) {
      case 'cellShaded':
        res.push(-1, -1);
        break;
      case 'cellTotal':
        const numbers = result[index + 1].split('\n').filter(n => {
          let b = false;
          for (var i = 0; i < n.length; i++) {
            if (n.charAt(i) !== ' ') {
              b = true;
              break;
            }
          }
          return b
        })
        for (let i = 0; i < 2; i++) {
          if (numbers.length > 0) {
            res.push(parseInt(numbers[numbers.length - 1]));
            numbers.pop();
          }
          else {
            res.push(-1)
          }
        }
        break;
      case 'cellNumber':
        res.push(0, 0);
    }
  })
  console.log(res)
  console.log(res.length)
  // console.log(kakuro_table_list)
  // console.log(kakuro_table_list['0'])

  // console.log($('body'))
  // console.log($('body').children().length)
})

// fs.readFile('./kakuro1.html', async function (err, html) {
//   if (err) {
//     throw err;
//   }
//   console.log(html)
//   // http.createServer(function (request, response) {
//   //   response.writeHeader(200, { "Content-Type": "text/html" });
//   //   response.write(html);
//   //   response.end();
//   // }).listen(8000);
// });

