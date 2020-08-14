var rfg = []; // yêu cầu dữ liệu
var tokn = 0;
function sdt(i, v) {
    var f = new FormData();
    f.append(i, v);
    var x = new XMLHttpRequest();
    x.open("POST", "/recv", !0);
    x.send(f);
    rfg.push(i);
    rfg = Array.from(new Set(rfg));
    senb(i, false);
}

function senb(i, v) { // set enable
    var c = document.getElementById(i);
    if (c == null)
        return;
    c = c.getElementsByTagName('*');
    for (var n of c) {
        n.disabled = !v;
    }
}
function shwlmnu() {
    document.getElementById("mnubtn").style.display = 'none';
    document.getElementsByClassName('lmnu')[0].style.display = 'block';
}

function hidelmnu() {
    document.getElementById("mnubtn").style.display = 'block';
    document.getElementsByClassName('lmnu')[0].style.display = 'none';
}

function oMnClk(i) {
    sdt(i, 'clkd');
    var mnus = document.getElementsByClassName('mnu');
    for (var j = 0; j < mnus.length; j++) {
        var e = mnus[j];
        if (e.id === i)
            e.style.display = 'block';
        else
            e.style.display = 'none';
    }
    hidelmnu();

}
function ajax() {
    var conn = new XMLHttpRequest();
    conn.timeout = 950;
    var cto = window.setTimeout(ctof, 1000);

    function ctof() {
        if (rfg.length > 0) // all là 1
            sdt('all', '');
        ajax();
        console.log("Request timed out");
    }
    conn.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            var res = conn.responseText;
            console.log(res);
            var o = JSON.parse(res);
            tokn= conn.getResponseHeader('tokn');
            for (x in o) {
                e = document.getElementById(x);
                rfg.splice(rfg.indexOf(x), 1);

                senb(x, true);
                if (e == null)
                    continue;
                var cls = e.getAttribute("class");
                var chdr = e.children;
                if (cls === "inptxt") {

                    if (chdr[1].value === '') {
                        chdr[1].value = o[x];
                        chdr[2].innerHTML = 'OK';
                    }

                } else if (cls === "sglbtn") {
                    if (chdr[0].innerHTML === '...')
                        chdr[0].innerHTML = o[x];
                } else if (cls === "txtvie") {
                    chdr[1].value = o[x];
                } else if (cls === "rng") {
                    if ((chdr[2] !== document.activeElement)) {
                        chdr[1].innerHTML = o[x];
                        chdr[2].value = o[x];
                    }

                } else if (cls === "swch") {
                    chdr[1].checked = o[x].toLowerCase() === 'true';
                } else if (cls === "state") {
                    chdr[1].checked = o[x].toLowerCase() === 'true';
                    chdr[1].disabled = true;
                } else if (cls === "tmpk") {
                    if ((chdr[3] !== document.activeElement) &&
                        (chdr[5] !== document.activeElement)) {
                        var val = parseInt(o[x]);
                        chdr[3].value = parseInt(val / 60);
                        chdr[5].value = val % 60;
                    }

                }

            };
            window.clearTimeout(cto);
            ajax();
        }
    };

    conn.open("POST", "/trans", !0);
    var f = new FormData();
    f.append('tokn', tokn);
    conn.send(f);
}

function onloadDone() {
    var hLst = document.createElement("datalist");
    var eHLsts = document.getElementsByClassName('hLst');
    for (var j = 0; j < eHLsts.length; j++) {
        for (var i = 0; i < 24; i++) {
            eHLsts[j].options.add(new Option(i, i));
        }
    };
    var eMLsts = document.getElementsByClassName('mLst');
    for (var j = 0; j < eMLsts.length; j++) {
        for (var i = 0; i < 60; i++) {
            eMLsts[j].options.add(new Option(i, i));
        }
    }
    sdt('all', '');
    document.getElementsByClassName('mnu')[2].style.display = 'block';// hiển thị menu đầu tiên
    ajax();
}
window.onload = onloadDone;