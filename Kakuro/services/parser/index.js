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


const parseKakuroFromHtml = (fileName) => {
  let width = 0;
  let height = 0;
  const res = []
  let row = [];
  let cells_index = 0
  fsReadFileHtml(fileName).then((htmlString) => {
    const $ = cheerio.load(htmlString);
    const kakuro_table_list = $("body > table > tbody > tr").map((index, element1) => {
      if (!width) width = $(element1).children().length;
      height++;

      return $(element1.children).map((_, element2) => {
        let isUpside = false;
        element2?.children?.forEach(e => {
          if (e?.attribs?.class === 'bottomNumber') {
            isUpside = true;
          }
        })

        const data = { class: $(element2).attr('class'), value: $(element2).text(), isUpside }
        if (data.class === undefined)
          return;

        cells_index++;
        switch (data.class) {
          case 'cellShaded':
            row.push(-1, -1);
            break;
          case 'cellTotal':
            const numbers = data.value.split('\n').map(s => s.trim()).filter(s => s.length > 0)
            if (numbers.length === 1) {
              numbers.unshift(-1);
              if (data.isUpside) numbers.reverse()
            }
            if (numbers.length > 2) {
              throw new Error('Invalid data')
            }

            for (let i = 1; i >= 0; i--) {
              row.push(parseInt(numbers[i]));
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
      });
    });
    fs.writeFileSync(path.join(__dirname, fileName.replace('html', 'json')), JSON.stringify(res))

    return res
  })

}

parseKakuroFromHtml('kakuro3.html')

