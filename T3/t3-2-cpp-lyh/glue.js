// import stubLoader from './ghost.js';
import stubLoader from './ghost.js'
var wasm_module = await stubLoader();

function mancalaOperator(a, b) {
    var inputarr = new Uint8Array(b);
    var ret = wasm_module.ccall("mancala_operator", "number",["number", "array"],[a,inputarr]);
    return ret;
}
function mancalaBoard(a, b, c) {
    const ptrb = wasm_module._malloc(b.length << 2);
    wasm_module.HEAP32.set(b, ptrb >> 2);
    var retarr = wasm_module._mancala_board(a,ptrb, c)>>2
    return wasm_module.HEAP32.slice(retarr, 15);
}

export {
    mancalaOperator,mancalaBoard
}