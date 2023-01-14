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
let width = 0;
let height = 0;

fsReadFileHtml("kakuro1.html").then((htmlString) => {
  const $ = cheerio.load(htmlString);
  const kakuro_table_list = $("body > table > tbody > tr").map((index, element1) => {
    if (!width) width = $(element1).children().length;
    height++;
    return $(element1.children).map((index, element2) => {
      return [$(element2).attr('class'), $(element2).text()]
    });
  });

  const result = []
  kakuro_table_list.each((index, element3) => {
    element3.each((index, element4) => {
      if (element4 !== undefined)
        result.push(element4.trim())

    })
  })
  const res = []
  let row = [];
  let cells_index = 0
  result.forEach((element, index) => {
    cells_index++;
    switch (element) {
      case 'cellShaded':
        row.push(-1, -1);
        break;
      case 'cellTotal':
        const numbers = result[index + 1].split('\n').map(s => s.trim()).filter(s => s.length > 0)
        for (let i = 0; i < 2; i++) {
          if (numbers.length > 0) {
            row.push(parseInt(numbers[numbers.length - 1]));
            numbers.pop();
          }
          else {
            row.push(-1)
          }
        }
        break;
      case 'cellNumber':
        row.push(0, 0);
        break;

      default:
        cells_index--;
        break;
    }

    if (cells_index && cells_index % width === 0 && row.length > 0) {
      res.push(row)
      row = []
    }
  })


  console.log(res)
  // console.log(res.length)
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

