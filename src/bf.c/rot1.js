var i;i=0;var j;j=0;var v;v=new Array;i++;v[i]=form.text.value.charCodeAt(j)|0;while(v[i]){v[i]=(v[i]|0)+1;i++;j++;v[i]=form.text.value.charCodeAt(j)|0};i--;while(v[i]){i--};i++;while(v[i]){document.write(String.fromCharCode(v[i]));i++};document.close()