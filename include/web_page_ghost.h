#pragma once
// Ghost Pod: Zusatz-Teile fuer das Dashboard (nur Bauvariante GHOST_POD=1).
// Werden in web_page.h per String-Verkettung eingesetzt; ohne Ghost Pod leer.
#include "config.h"

#if GHOST_POD
#define GHOST_CSS R"rawliteral(
/* --- Ghost Pod --- */
.gp{max-width:1200px;margin:0 auto 16px;background:var(--card);border-radius:12px;padding:18px;box-shadow:0 1px 3px var(--shadow);border-top:4px solid var(--red)}
.gh{display:flex;justify-content:space-between;align-items:baseline;flex-wrap:wrap;gap:6px}
.leds{display:grid;grid-template-columns:repeat(4,1fr);gap:10px;margin:16px 0 10px}
.ld{text-align:center}
.bulb{width:46px;height:46px;border-radius:50%;margin:0 auto 8px;background:#3a2326;border:2px solid #552b30;transition:.25s}
.bulb.on{background:#ff3b3b;border-color:#ff8a8a;box-shadow:0 0 18px #ff3b3b,0 0 40px #ff3b3b88}
.ld .nm{font-weight:600;font-size:13.5px}.ld .th{color:var(--dim);font-size:12px;font-variant-numeric:tabular-nums}
.ld .ct{color:var(--dim);font-size:11.5px;margin-top:2px}
.bar{height:6px;background:var(--line);border-radius:3px;overflow:hidden;margin-top:6px}
.bar i{display:block;height:100%;background:var(--red);transition:width .5s}
.g2{display:grid;grid-template-columns:repeat(auto-fit,minmax(280px,1fr));gap:16px;max-width:1200px;margin:0 auto 16px}
.g2 .wide{margin:0;max-width:none}
.act i{background:var(--orange)}
.gr{display:inline-block;width:10px;height:10px;border-radius:50%;background:#1d3a24;margin-left:6px;vertical-align:middle}
.gr.on{background:var(--green);box-shadow:0 0 8px var(--green)}
.lidwrap{display:flex;gap:22px;align-items:center;flex-wrap:wrap;justify-content:center;margin-top:14px}
.lid{width:220px;height:220px;flex:0 0 auto}
.lid .rim{fill:#1b1b1f;stroke:#000;stroke-width:6}
.lid .lbl2{fill:#8a5a3a;opacity:.55}
.lid .led{stroke:#000;stroke-width:2;transition:fill .15s,filter .15s}
.lid .r{fill:#3a2326}.lid .r.on{fill:#ff3b3b;filter:url(#glowR)}
.lid .g{fill:#1d3a24}.lid .g.on{fill:#3fdc5a;filter:url(#glowG)}
.lid .ant{fill:#c9ccd3;stroke:#777;stroke-width:1.5}
.lid text{font:10px system-ui,sans-serif;fill:var(--dim)}
.lidwrap .leds{flex:1;min-width:280px;margin:0}
@media(max-width:520px){.bulb{width:34px;height:34px}.ld .nm{font-size:12px}}
)rawliteral"
#define GHOST_HTML R"rawliteral(
<div class="gp">
 <div class="gh"><div class="lbl">&#128123; Ghost hunt &middot; <span id="gph">-</span><span class="gr" id="gs"></span><span class="gr" id="gb"></span></div>
 <div class="sub">best diff this round: <b id="grb">-</b></div></div>
 <div class="bar"><i id="gbar" style="width:0"></i></div>
 <div class="lidwrap">
 <svg class="lid" viewBox="0 0 220 220" aria-label="Lid of the Ghost Pod">
  <defs>
   <filter id="glowR" x="-1" y="-1" width="3" height="3"><feGaussianBlur stdDeviation="4" result="b"/><feMerge><feMergeNode in="b"/><feMergeNode in="SourceGraphic"/></feMerge></filter>
   <filter id="glowG" x="-1" y="-1" width="3" height="3"><feGaussianBlur stdDeviation="4" result="b"/><feMerge><feMergeNode in="b"/><feMergeNode in="SourceGraphic"/></feMerge></filter>
  </defs>
  <circle class="rim" cx="110" cy="110" r="100"/>
  <circle class="lbl2" cx="110" cy="110" r="78"/>
  <circle class="ant" cx="110" cy="110" r="9"/><circle cx="110" cy="110" r="3" fill="#888"/>
  <circle class="led r" id="d2" cx="40"  cy="110" r="10"/><text x="40"  y="134" text-anchor="middle">9</text>
  <circle class="led r" id="d3" cx="110" cy="40"  r="10"/><text x="110" y="22"  text-anchor="middle">12</text>
  <circle class="led r" id="d4" cx="180" cy="110" r="10"/><text x="180" y="134" text-anchor="middle">3</text>
  <circle class="led r" id="d5" cx="110" cy="182" r="10"/><text x="110" y="208" text-anchor="middle">&#9829;</text>
  <circle class="led g" id="d0" cx="62"  cy="162" r="9"/>
  <circle class="led g" id="d1" cx="158" cy="162" r="9"/>
 </svg>
 <div class="leds">
  <div class="ld"><div class="bulb" id="l0"></div><div class="nm">Activity</div><div class="th" id="t0">-</div><div class="ct" id="c0"></div></div>
  <div class="ld"><div class="bulb" id="l1"></div><div class="nm">Share</div><div class="th" id="t1">-</div><div class="ct" id="c1"></div></div>
  <div class="ld"><div class="bulb" id="l2"></div><div class="nm">Highscore</div><div class="th" id="t2">-</div><div class="ct" id="c2"></div></div>
  <div class="ld"><div class="bulb" id="l3"></div><div class="nm">BLOCK</div><div class="th" id="t3">-</div><div class="ct" id="c3"></div></div>
 </div>
 </div>
 <div class="sub" style="text-align:center">LED 1 = half the pool diff (sign of life) &middot; LED 2 = real share &middot; LED 3 = <span id="hsl">all-time high score</span> beaten &middot; LED 4 = real block</div>
 <div class="sub" style="text-align:center;margin-top:10px"><button class="swbtn" onclick="ledTest()">&#128161; LED test</button>
 <span id="ltest" style="margin-left:8px;font-weight:600"></span></div>
 <div class="sub" id="pdiag" style="text-align:center;margin-top:6px"></div>
</div>
<div class="g2">
 <div class="wide"><div class="lbl">&#128225; Antenna (last sniff)</div><table>
  <tr><td>Channel</td><td id="kan">-</td></tr>
  <tr><td>Antenna (<span id="pb">33</span>)</td><td id="tb">-</td></tr>
  <tr><td>Copper band / ground (<span id="pa">32</span>)</td><td id="ta">-</td></tr>
  <tr><td>Noise (ADC)</td><td id="adc">-</td></tr>
  <tr><td>Ghost activity</td><td><span id="act">-</span><div class="bar act"><i id="actb" style="width:0"></i></div></td></tr>
  <tr><td>Ghost number &middot; digit sum</td><td id="gz">-</td></tr>
  <tr><td>Temperature (rough)</td><td id="tmp">-</td></tr>
  <tr><td>Ghost starting point</td><td id="seed" style="font-family:monospace">-</td></tr>
 </table></div>
 <div class="wide"><div class="lbl">&#128220; Ghost chronicle</div><table>
  <tr><td>Rounds</td><td id="hr0">-</td></tr>
  <tr><td>Activity / shares / high scores / blocks (rounds)</td><td id="hl">-</td></tr>
  <tr><td>Best difficulty of all time</td><td id="hb">-</td></tr>
  <tr><td>Accepted shares</td><td id="hsh">-</td></tr>
  <tr><td>Blocks (poltergeist)</td><td id="hbl">-</td></tr>
  <tr><td>Total uptime</td><td id="hu">-</td></tr>
  <tr id="e26r" style="display:none"><td>Era 2.6 (counting zeros)</td><td id="e26">-</td></tr>
 </table></div>
</div>
)rawliteral"
#define GHOST_JS R"rawliteral(
function fl(s){const y=Math.floor(s/31536000);s%=31536000;const d=Math.floor(s/86400);s%=86400;
 return(y?y+'y ':'')+(y||d?d+'d ':'')+Math.floor(s/3600)+'h '+Math.floor(s/60)%60+'min'}
async function ledTest(){try{await fetch('/api/ledtest',{method:'POST'})}catch(e){}}
function lid(g){if(!g.pins)return;
 g.pins.forEach((p,i)=>{const e=$('d'+i);if(!e)return;
  e.classList.toggle('on',!!p.out);
  const t=e.querySelector('title')||e.appendChild(document.createElementNS('http://www.w3.org/2000/svg','title'));
  t.textContent='GPIO '+p.pin+' – '+p.name+(p.rtc?' (touch driver!)':'')})}
function ghost(g){if(!g)return;lid(g);
 $('ltest').textContent=g.test>=0?'now lit: GPIO '+g.test+' = '+g.testName:'';
 if(g.pins)$('pdiag').textContent='Pins: '+g.pins.map(p=>p.pin+(p.out?' on':' off')+(p.rtc?' (touch driver!)':'')).join(' · ')+(g.reclaims?' · '+g.reclaims+'× reclaimed':'');
 $('gph').textContent=g.phase+(g.phase==='searching'?' ('+g.roundLeft+' s)':'');
 $('gbar').style.width=(g.phase==='searching'?100*(g.roundLen-g.roundLeft)/g.roundLen:g.phase==='result'?100:0)+'%';
 $('grb').textContent=g.roundBest?fd(g.roundBest):'-';
 const t=Date.now(),scan=g.phase==='scan'||g.sniffing;
 $('gs').className='gr'+((scan?(t/160|0)%2:g.phase==='searching')?' on':'');
 $('gb').className='gr'+((scan?(t/160|0)%2:g.phase==='searching'&&(t/1000|0)%2)?' on':'');
 $('hsl').textContent=g.hsHours?'high score of the last '+g.hsHours+' h':g.bridge?'all-time high score (bridge in)':'high score since start (bridge out)';
 for(let k=0;k<4;k++){$('l'+k).className='bulb'+((g.lit>>k&1)||(k===3&&g.blockLed)?' on':'');
  $('t'+k).textContent=g.thr[k]?'≥ '+fd(g.thr[k]):'-';$('c'+k).textContent=g.hist.led[k]+'× seen'}
 const a=g.ant;$('pa').textContent=a.pinA;$('pb').textContent=a.pinB;
 $('ta').textContent=a.a+' (base '+a.baseA+', ±'+a.jA+')';$('tb').textContent=a.b+' (base '+a.baseB+', ±'+a.jB+')';
 $('kan').textContent='\u{1F4E1} '+(a.seg?a.seg+' of '+a.segs+' segments out':'retracted')+' · ~'+a.cm+' cm · ~'+a.mhz+' MHz';
 $('adc').textContent=a.adc+' · '+a.n+' readings';$('act').textContent=a.act;
 $('actb').style.width=Math.min(100,a.act*4)+'%';
 $('gz').textContent=a.ghost?a.ghost+' · '+a.qs:'-';$('tmp').textContent=a.temp+' °C';$('seed').textContent=a.seed||'-';
 const h=g.hist;$('hr0').textContent=h.rounds+' · '+h.sniffs+'× sniffed';$('hl').textContent=h.led.join(' / ');
 $('hb').textContent=fd(h.best);$('hbl').textContent=h.blocks;$('hsh').textContent=h.shares;$('hu').textContent=fl(h.uptime);
 if(g.era26){$('e26r').style.display='';const e=g.era26;
  $('e26').textContent=e.scans+' Scans · '+e.led.join(' / ')+' · '+fl(e.uptime)}}
)rawliteral"
#define GHOST_TICK "ghost(s.ghost);"
#define PAGE_TITLE "Ghost Pod"
#define GHOST_TICK_MS "1000"
#else
#define GHOST_CSS ""
#define GHOST_HTML ""
#define GHOST_JS ""
#define GHOST_TICK ""
#define PAGE_TITLE "ESP32 Miner"
#define GHOST_TICK_MS "3000"
#endif
