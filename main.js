const canvas = document.querySelector('canvas');
const ctx = canvas.getContext('2d');

$(document).ready(function(){
    $.getJSON("./json/out/res.json", function(data){
        draw_table(data);
    }).fail(function(){
        console.log("An error has occurred.");
    });
});

function draw_table(data) {
    // init
    const nb_promotions = data['schedule']['day_1']['slot_1'].length;
    const offset_x = 10;
    const offset_y = 50;
    const cell_height = 100;
    const cols = 5;
    const rows = 4;
    const scale = 1000/(Math.max(cols,rows));
    const width = canvas.width = window.innerWidth - 20;
    const height = canvas.height = nb_promotions*rows*cell_height + 
        offset_y*2 + ((nb_promotions-1)*offset_y);
    const cell_width = (width - offset_x*2)/cols;
    let x = offset_x;
    let y = offset_y;

    // draw table
    for (let k = 0; k < nb_promotions; k++) {
        ctx.font = '20px serif';
        ctx.fillStyle = "black";
        ctx.fillText(data['schedule']['day_1']['slot_1'][k].training 
            + ' group ' + data['schedule']['day_1']['slot_1'][k].group_id, 
            5 + offset_x, offset_y*(k+1) + rows*cell_height*k - 15);
    }
    for (let i = 0; i < cols; i++) {
        for (let j = 0; j < rows; j++) {
            for (let k = 0; k < nb_promotions; k++) {
                y = offset_y*(k+1) + rows*cell_height*k + j * cell_height;
                switch (data['schedule']['day_' + (i+1).toString()]
                        ['slot_'+ (j+1).toString()][k].subject) {
                    case "Computer-Science" :
                        ctx.fillStyle = "lightgreen";
                        ctx.fillRect(x, y, cell_width, cell_height);
                        break;
                    case "Physics" :
                        ctx.fillStyle = "orange";
                        ctx.fillRect(x, y, cell_width, cell_height);
                        break;
                    case "Mathematics" :
                        ctx.fillStyle = "yellow";
                        ctx.fillRect(x, y, cell_width, cell_height);
                        break;
                    case "English" :
                        ctx.fillStyle = "lightblue";
                        ctx.fillRect(x, y, cell_width, cell_height);
                        break;
                    default :
                        ctx.fillStyle = "lightgray";
                        ctx.fillRect(x, y, cell_width, cell_height);
                        break;
                }
                if (data['schedule']['day_' + (i+1).toString()]
                        ['slot_'+ (j+1).toString()][k].room_id !== -1) {
                    ctx.font = '20px serif';
                    ctx.fillStyle = "black";
                    ctx.fillText(data['schedule']['day_'+(i+1).toString()]
                        ['slot_'+ (j+1).toString()][k].subject + ' ' +
                        data['schedule']['day_'+(i+1).toString()]
                        ['slot_'+ (j+1).toString()][k].room_type, x+5, y+25);
                    ctx.fillText('Room n°' +
                        data['schedule']['day_'+(i+1).toString()]
                        ['slot_'+ (j+1).toString()][k].room_id, x+5, y+50);
                    ctx.fillText('Teacher n°' +
                        data['schedule']['day_'+(i+1).toString()]
                        ['slot_'+ (j+1).toString()][k].teacher_id, x+5, y+75);
                }
                ctx.rect(x, y, cell_width, cell_height);
                ctx.lineWidth = 2;
                ctx.strokeStyle = "black";
                ctx.stroke();
            }
        }
        x += cell_width;
    }
}